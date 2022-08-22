void memset (int *ptr, int n, int value)
{
  int i;

  for (i=0; i < n; ++i, ++ptr)
    *ptr = value;
}
