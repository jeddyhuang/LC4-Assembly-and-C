#include "lc4libc.h"
#include "chess_sprites.h"

/*
 * ############# CONSTANTS ######################
 */

// Piece codes lower 3 bits - Pawn 1, Rook 2, Knight 3, Bishop 4, Queen 5, King 6
// Color encoded in 4th bit 1 for white 0 for black

// Piece type encoded in lower 3 bits
#define PAWN     1
#define ROOK     2
#define KNIGHT   3
#define BISHOP   4
#define QUEEN    5
#define KING     6

// Piece color encoded in 4th bit
#define BLACK_PAWN     1
#define BLACK_ROOK     2
#define BLACK_KNIGHT   3
#define BLACK_BISHOP   4
#define BLACK_QUEEN    5
#define BLACK_KING     6

#define WHITE_PAWN     9
#define WHITE_ROOK     10
#define WHITE_KNIGHT   11
#define WHITE_BISHOP   12
#define WHITE_QUEEN    13
#define WHITE_KING     14

#define SQUARE_SIZE    15

#define WHITE_SQUARE_COLOR  0x2108U
#define BLACK_SQUARE_COLOR  0x0100U
#define BLACK_PIECE_COLOR   0x0000U
#define WHITE_PIECE_COLOR   0x7FFFU


/*
 * #############  DATA STRUCTURES THAT STORE THE GAME STATE ######################
 */

// 2D array of pieces game board_state[rank][file]

int board_state[8][8] = {
  {WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK},
  {WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN},
  {BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK}
};

int player_to_move = 1; // 1 for white, 0 for black
int en_passant = 0; // 1 for true
int pwn_rank = -1;
int pwn_file = -1;

// Encodes information about castling status
struct {
  int white_short_ok, white_long_ok;
  int black_short_ok, black_long_ok;
} castle;


/*
 * #############  UTILITY ROUTINES ######################
 */

int abs(int x)
{
  return ( (x >= 0) ? x : -x );
}

int max(int x, int y)
{
  return ( (x > y) ? x : y );
}

//
// routine for printing out 2C 16 bit numbers on the ASCII display
//
void printnum (int n) {
  int abs_n;
  char str[10], *ptr;

  // Corner case (n == 0)
  if (n == 0) {
    lc4_puts ((lc4uint*)"0");
    return;
  }
 
  abs_n = (n < 0) ? -n : n;

  // Corner case (n == -32768) no corresponding +ve value
  if (abs_n < 0) {
    lc4_puts ((lc4uint*)"-32768");
    return;
  }

  ptr = str + 10; // beyond last character in string

  *(--ptr) = 0; // null termination

  while (abs_n) {
    *(--ptr) = (abs_n % 10) + 48; // generate ascii code for digit
    abs_n /= 10;
  }

  // Handle -ve numbers by adding - sign
  if (n < 0) *(--ptr) = '-';

  lc4_puts((lc4uint*)ptr);
}

void endl () {
  lc4_puts((lc4uint*)"\n");
}

/*
 * #############  CODE TO ENTER MOVES ######################
 */

// This struct stores the ply we are currently considering.
// The ply indicates a source square and a dest square.
struct {
  int rank_src, file_src;
  int rank_dst, file_dst;
  int castle; // 0 for no castle, 1 for castle short, 2 for castle long
} ply;

// Gets the current ply from the user or halts
int get_ply ()
{
  char input;

  ply.castle = 0; // no castle

  // get source file
  input = lc4_getc_echo();
  if (input == 'q') return -2;

  if (input == 'x') { //castle short
    ply.castle = 1;
    return 1;
  }

  if (input == 'y') { // castle long
    ply.castle = 2;
    return 1; 
  }
  
  if ((input < 'a') || (input > 'h')) return -1;
  ply.file_src = (int) (input - 'a');

  // get source rank
  input = lc4_getc_echo();
  if (input == 'q') return -2;
  if ((input < '1') || (input > '8')) return -1;
  ply.rank_src = (int) (input - '1');
  
  // get dest file
  input = lc4_getc_echo();
  if (input == 'q') return -2;
  if ((input < 'a') || (input > 'h')) return -1;
  ply.file_dst = (int) (input - 'a');

  // get dest rank
  input = lc4_getc_echo();
  if (input == 'q') return -2;
  if ((input < '1') || (input > '8')) return -1;
  ply.rank_dst = (int) (input - '1');
  
  return 1;
}


/*
 * #############  CODE THAT DRAWS THE SCENE ######################
 */

void draw_square (int rank, int file)
{
  lc4int start_row, start_col;
  lc4uint piece_code, piece_type, piece_color, color;
  lc4uint *piece_sprite;

  start_row = (7 - rank)*SQUARE_SIZE + 2;
  start_col = file*15 + 4;

  // Draw the board square
  color = ((rank + file) & 1) ? WHITE_SQUARE_COLOR : BLACK_SQUARE_COLOR;
  lc4_draw_rect(start_col, start_row, SQUARE_SIZE, SQUARE_SIZE, color);

  // Draw the piece
  piece_code = board_state[rank][file];
  if (piece_code) {
    piece_type = piece_code & 0x7;
    piece_color = (piece_code & 8) ? WHITE_PIECE_COLOR : BLACK_PIECE_COLOR;

    if(piece_type == PAWN)   piece_sprite = pawn_sprite;
    if(piece_type == ROOK)   piece_sprite = rook_sprite;
    if(piece_type == KNIGHT) piece_sprite = knight_sprite;
    if(piece_type == BISHOP) piece_sprite = bishop_sprite;
    if(piece_type == QUEEN)  piece_sprite = queen_sprite;
    if(piece_type == KING)   piece_sprite = king_sprite;
    
    lc4_draw_sprite(start_col, start_row, piece_color, piece_sprite);
  }
}

void draw_chessboard ()
{
  int rank, file;
  
  for (rank=0; rank < 8; ++rank) {
    for (file=0; file < 8; ++file) {
      draw_square(rank, file);
    }
  }
}

/*
 * #############  CODE THAT HANDLES GAME PLAY ######################
 */


int is_legal_pawn_move (int rank_src, int file_src, int rank_dst, int file_dst, int piece_color)
{
  int rank_change, file_change, piece_code_dst;
  
  // Make sure you are moving in the right direction
  if (piece_color) {
    // White pawn
    if (rank_dst <= rank_src) return 0;
  } else {
    // Black pawn
    if (rank_dst >= rank_src) return 0;
  }

  rank_change = abs(rank_dst - rank_src);
  file_change = abs(file_dst - file_src);

  if (file_change > 1) {
    return 0;
  } else {
    if (file_change) {
      // Change of file by 1

      if (rank_change != 1) {
    return 0;
      } else {
    // Diagonal move detected
    piece_code_dst = board_state[rank_dst][file_dst];

    if (piece_code_dst) {
      // You must be capturing a piece of the oposite color
      if ((piece_code_dst & 8) == piece_color) return 0;
    } else {
      if ((pwn_rank != -1) && (pwn_file != -1)) {
        if (rank_src != pwn_rank) return 0;
        if (file_dst != pwn_file) return 0;
        en_passant = 1;
      } else return 0;
    }
      }

    } else {
      // Moving straight on same file

      if (rank_change > 2) {
    return 0;
      } else {

    // Check that final square is empty
    if (board_state[rank_dst][file_dst]) return 0;

    if (rank_change == 2) {
      // Check that this is the pawns first move
      if ( (rank_src == 1) || (rank_src == 6) ) {
        // Check that middle square is empty
        if (board_state[(rank_dst+rank_src)/2][(file_dst+file_src)/2]) return 0;
      } else {
        return 0;
      }
    }
      }
    }
  }

  // Check for promotion to Queen. Note special case of choosing a Knight not accounted for
  if (rank_dst == 0) board_state[rank_dst][file_dst] = BLACK_QUEEN;
  if (rank_dst == 7) board_state[rank_dst][file_dst] = WHITE_QUEEN;
  
  if (rank_change == 2) {
    pwn_rank = rank_dst;
    pwn_file = file_dst;
  } else {
    if (en_passant == 0) {
      pwn_rank = -1;
      pwn_file = -1;
    }
  }
  
  return 1;
}

int is_clear_path (int rank_src, int file_src, int rank_dst, int file_dst)
{
  int dx, dy, length, i;

  dx = file_dst - file_src;
  dy = rank_dst - rank_src;

  length = max(abs(dx), abs(dy));

  if (dx < 0) dx = -1;
  if (dx > 0) dx =  1;

  if (dy < 0) dy = -1;
  if (dy > 0) dy =  1;

  // Check that all the squares between the src and dst are clear
  for (i=1; i < length; ++i)
    if (board_state[rank_src + i*dy][file_src + i*dx])
      return 0;
  
  return 1;
}

int is_legal_rook_move (int rank_src, int file_src, int rank_dst, int file_dst)
{
  int rank_change, file_change;
  
  rank_change = abs(rank_dst - rank_src);
  file_change = abs(file_dst - file_src);
  
  if ((rank_change == 0) || (file_change == 0)) {
    if (is_clear_path(rank_src, file_src, rank_dst, file_dst)){  
      pwn_rank = -1;
      pwn_file = -1;
      return 1;
    }
  }
  
  return 0;
}

int is_legal_bishop_move (int rank_src, int file_src, int rank_dst, int file_dst)
{
  int rank_change, file_change;
  
  rank_change = abs(rank_dst - rank_src);
  file_change = abs(file_dst - file_src);
  
  if (rank_change == file_change) {
    if (is_clear_path(rank_src, file_src, rank_dst, file_dst)){
      pwn_rank = -1;
      pwn_file = -1;
      return 1;
    }
  }
  
  return 0;
}

int is_legal_knight_move (int rank_src, int file_src, int rank_dst, int file_dst)
{
  int rank_change, file_change;
  
  rank_change = abs(rank_dst - rank_src);
  file_change = abs(file_dst - file_src);
  
  if (((rank_change == 1) && (file_change == 2)) || ((rank_change == 2) && (file_change == 1))) return 1;
  
  return 0;
}

int is_legal_queen_move (int rank_src, int file_src, int rank_dst, int file_dst)
{
  int rank_change, file_change;
  
  rank_change = abs(rank_dst - rank_src);
  file_change = abs(file_dst - file_src);
  
  if ((rank_change == file_change) || (rank_change == 0) || (file_change == 0)) {
    if (is_clear_path(rank_src, file_src, rank_dst, file_dst)){
      pwn_rank = -1;
      pwn_file = -1;
      return 1;
    }
  }
  
  return 0;
}

int is_legal_king_move (int rank_src, int file_src, int rank_dst, int file_dst)
{
  int rank_change, file_change;
  
  rank_change = abs(rank_dst - rank_src);
  file_change = abs(file_dst - file_src);
  
  if ((rank_change < 2) && (file_change < 2)) {
    pwn_rank = -1;
    pwn_file = -1;
    return 1;
  }
  
  return 0;
}

int is_legal_piece_move (int rank_src, int file_src, int rank_dst, int file_dst)
{
  int piece_code_src, piece_code_dst;
  int piece_color_dst, piece_color_src;
  int piece_type;

  // Check if source and destination are the same square
  if ((rank_src == rank_dst) && (file_src == file_dst)) return 0;

  piece_code_src = board_state[rank_src][file_src];
  if (piece_code_src == 0) return 0;

  piece_color_src = piece_code_src & 0x8;

  piece_code_dst = board_state[rank_dst][file_dst];

  // Checks if you are trying to move to a square occupied by a piece of the same color
  if (piece_code_dst) {
    piece_color_dst = piece_code_dst & 0x8;
    if (piece_color_src == piece_color_dst) return 0;
  }

  // get piece type
  piece_type = piece_code_src & 0x7;

  if (piece_type == PAWN)
    return is_legal_pawn_move(rank_src, file_src, rank_dst, file_dst, piece_color_src);

  if (piece_type == ROOK)
    return is_legal_rook_move(rank_src, file_src, rank_dst, file_dst);

  if (piece_type == KNIGHT)
    return is_legal_knight_move(rank_src, file_src, rank_dst, file_dst);

  if (piece_type == BISHOP)
    return is_legal_bishop_move(rank_src, file_src, rank_dst, file_dst);

  if (piece_type == QUEEN)
    return is_legal_queen_move(rank_src, file_src, rank_dst, file_dst);
  
  if (piece_type == KING)
    return is_legal_king_move(rank_src, file_src, rank_dst, file_dst);

  return 1;
}

int is_king_in_check (int king_rank, int king_file, int test_rank, int test_file)
{
  int rank, file, king_code, retcode=0;

  // Move king to test location
  king_code = board_state[king_rank][king_file];
  board_state[king_rank][king_file] = 0;
  board_state[test_rank][test_file] = king_code;

  // For each piece check if it can attack the king
  for (rank=0; rank < 8; ++rank) {
    for (file=0; file < 8; ++file) {
      if (is_legal_piece_move (rank, file, test_rank, test_file)) {
    retcode = 1;
      }
    }
  }

  // Move king back
  board_state[test_rank][test_file] = 0;
  board_state[king_rank][king_file] = king_code;

  return retcode;
}

int is_legal_ply ()
{
  int piece_code_src, piece_code_dst, player_color;
  int pawn_code, en_passant_temp, pwn_rank_temp, pwn_file_temp;
  int rank, file, king_rank, king_file, king_code;

  piece_code_src = board_state[ply.rank_src][ply.file_src];
  piece_code_dst = board_state[ply.rank_dst][ply.file_dst];
  
  en_passant_temp = en_passant;
  pwn_rank_temp = pwn_rank;
  pwn_file_temp = pwn_file;

  if (piece_code_src == 0) {
    lc4_puts ((lc4uint*)"\n No piece selected \n");
    return 0;
  } else {
    player_color = (piece_code_src & 8) ? 1 : 0;
  }

  // Check that the right player is moving
  if ( player_color != player_to_move ) {
    lc4_puts ((lc4uint*)"\n Other side to move \n");
    return 0;
  }

  if (is_legal_piece_move(ply.rank_src, ply.file_src, ply.rank_dst, ply.file_dst)) {
  
    board_state[ply.rank_src][ply.file_src] = 0;
    board_state[ply.rank_dst][ply.file_dst] = piece_code_src;
    
    if (en_passant) {
      pawn_code = board_state[pwn_rank][pwn_file];
      board_state[pwn_rank][pwn_file] = 0;
    }

    // Get king position
    king_code = player_to_move ? WHITE_KING : BLACK_KING;
    for (rank=0; rank < 8; ++rank) {
      for (file=0; file < 8; ++file) {
    if (board_state[rank][file] == king_code) {
      king_rank = rank;
      king_file = file;
    }
      }
    }
  
    if (is_king_in_check(king_rank, king_file, king_rank, king_file)) {
      lc4_puts ((lc4uint*)"\n Bad Move - King would be in check! \n");

      // Restore board to original state
      board_state[ply.rank_src][ply.file_src] = piece_code_src;
      board_state[ply.rank_dst][ply.file_dst] = piece_code_dst;
      
      if (en_passant) board_state[pwn_rank][pwn_file] = pawn_code;
      
      en_passant = en_passant_temp;
      pwn_rank = pwn_rank_temp;
      pwn_file = pwn_file_temp;

      return 0;
    } else {
      return 1;
    }

  } else
    return 0;
}

void init_castle_status ()
{
  castle.white_short_ok = 1;
  castle.white_long_ok  = 1;
  castle.black_short_ok = 1;
  castle.black_long_ok  = 1;
}

void update_castle_status()
{
  if ( (ply.rank_src == 0) && (ply.file_src == 0) ) // moved the white rook long
    castle.white_long_ok = 0;
  
  if ( (ply.rank_src == 0) && (ply.file_src == 7) ) // moved the white rook short
    castle.white_short_ok = 0;
   
  if ( (ply.rank_src == 0) && (ply.file_src == 4) ) { // moved the white king
    castle.white_short_ok = 0;
    castle.white_long_ok = 0;
  }

  if ( (ply.rank_src == 7) && (ply.file_src == 0) ) // moved the black rook long
    castle.white_long_ok = 0;
  
  if ( (ply.rank_src == 7) && (ply.file_src == 7) ) // moved the black rook short
    castle.white_short_ok = 0;
   
  if ( (ply.rank_src == 7) && (ply.file_src == 4) ) { // moved the black king
    castle.white_short_ok = 0;
    castle.white_long_ok = 0;
  }
}

int test_castle_checks (int king_rank, int king_file, int start_file, int end_file)
{
  int file;

  for (file=start_file; file <= end_file; ++file) {
    if (is_king_in_check(king_rank, king_file, king_rank, file))
      return 0;
  }

  return 1;
}

int handle_short_castle ()
{
  if (player_to_move) { // white
      
    if (castle.white_short_ok && is_clear_path(0,4,0,7)) {
      if (test_castle_checks(0,4,4,6)) {
    board_state[0][4] = 0;
    board_state[0][5] = WHITE_ROOK;
    board_state[0][6] = WHITE_KING;
    board_state[0][7] = 0;

    draw_square(0,4);
    draw_square(0,5);
    draw_square(0,6);
    draw_square(0,7);

    castle.white_short_ok = 0;
    castle.white_long_ok = 0;
    
    return 1;
      }
    }

  } else { // black
    
    if (castle.black_short_ok && is_clear_path(7,4,7,7)) {
      if (test_castle_checks(7,4,4,6)) {
    board_state[7][4] = 0;
    board_state[7][5] = BLACK_ROOK;
    board_state[7][6] = BLACK_KING;
    board_state[7][7] = 0;

    draw_square(7,4);
    draw_square(7,5);
    draw_square(7,6);
    draw_square(7,7);
    
    castle.black_short_ok = 0;
    castle.black_long_ok = 0;
    
    return 1;
      }
    }
  }

  return 0;
}

int handle_long_castle ()
{  
  if (player_to_move) { // white
    
    if (castle.white_long_ok && is_clear_path(0,0,0,4)) {
      if (test_castle_checks(0,4,2,4)) {
    board_state[0][0] = 0;
    board_state[0][2] = WHITE_KING;
    board_state[0][3] = WHITE_ROOK;
    board_state[0][4] = 0;

    draw_square(0,0);
    draw_square(0,2);
    draw_square(0,3);
    draw_square(0,4);
    
    castle.white_short_ok = 0;
    castle.white_long_ok = 0;
    
    return 1;
      }
    }
  } else { // black
    
    if (castle.black_long_ok && is_clear_path(7,0,7,4)) {
      if (test_castle_checks (7,4,2,4)) {
    board_state[7][0] = 0;
    board_state[7][2] = BLACK_KING;
    board_state[7][3] = BLACK_ROOK;
    board_state[7][4] = 0;

    draw_square(7,0);
    draw_square(7,2);
    draw_square(7,3);
    draw_square(7,4);
    
    castle.black_short_ok = 0;
    castle.black_long_ok = 0;
    
    return 1;
      }
    }
  }

  return 0;
}

int handle_castle ()
{
  if (ply.castle == 1)
    return handle_short_castle();

  if (ply.castle == 2)
    return handle_long_castle();

  return 0;
}

/*
 * #############  MAIN PROGRAM ######################
 */

int main ()
{
  lc4int retcode;
  
  lc4_puts ((lc4uint*)"!!! Welcome to LC4 Chess !!!\n");

  draw_chessboard ();

  init_castle_status();

  player_to_move = 1; // white moves first

  while (1) {

    if (player_to_move)
      lc4_puts ((lc4uint*)"\n White to move \n");
    else
      lc4_puts ((lc4uint*)"\n Black to move \n");
    
    // Get the next ply from the user
    retcode = get_ply();

    if (retcode == -1) {
      lc4_puts ((lc4uint*)"\nBad PLY entered\n");
    }

    if (retcode == -2) {
      lc4_puts ((lc4uint*)"\nGame Ending\n");
      lc4_halt();
    }

    if (retcode == 1) {
      if (ply.castle) {
    if (handle_castle()) {
      // Update player to move next
      player_to_move = 1 - player_to_move;
    } else {
      lc4_puts ((lc4uint*)"\n Illegal Castle! \n");
    }
      } else {
    if (is_legal_ply()) {
      lc4_puts ((lc4uint*)"\nLegal Move\n");
      
      draw_square (ply.rank_dst, ply.file_dst);
      draw_square (ply.rank_src, ply.file_src);
      
      if (en_passant) {
        draw_square (pwn_rank, pwn_file);
        en_passant = 0;
        pwn_rank = -1;
        pwn_file = -1;
      }

      update_castle_status();
      
      // Update player to move next
      player_to_move = 1 - player_to_move;
    } else {
      lc4_puts ((lc4uint*)"\nIllegal Move!!\n");
    }
      }
    }
  }


  return 0;
}
