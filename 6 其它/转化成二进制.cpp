void To_string_base2(LL n,string &s){
  while(n > 0){
    if(n&1)
      s += "1";
    else
      s += "0";
    n >>= 1;
  };
  reverse(s.begin(),s.end());
}

  while((int)s.size() < n)
        s = "0"+s;
