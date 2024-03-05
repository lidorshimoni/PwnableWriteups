int ropme()
{
  char s[100]; // [esp+4h] [ebp-74h] BYREF
  int input; // [esp+68h] [ebp-10h] BYREF
  int fd; // [esp+6Ch] [ebp-Ch]

  printf("Select Menu:");
  __isoc99_scanf("%d", &input);
  getchar();
  if ( input == a )
  {
    A();
  }
  else if ( input == b )
  {
    B();
  }
  else if ( input == c )
  {
    C();
  }
  else if ( input == d )
  {
    D();
  }
  else if ( input == e )
  {
    E();
  }
  else if ( input == f )
  {
    F();
  }
  else if ( input == g )
  {
    G();
  }
  else
  {
    printf("How many EXP did you earned? : ");
    gets(s);
    if ( atoi(s) == sum )
    {
      fd = open("flag", 0);
      s[read(fd, s, 0x64u)] = 0;
      puts(s);
      close(fd);
      exit(0);
    }
    puts("You'd better get more experience to kill Voldemort");
  }
  return 0;
}