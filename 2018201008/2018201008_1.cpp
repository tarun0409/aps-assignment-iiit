#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
struct number
{
  string value;
  char sign;
};
class BigInteger
{
  public:
  struct number number1;
  BigInteger()
  {
    number1.value = "0";
    number1.sign = '+';
  }
  BigInteger(string num)
  {
    if(num.length()==0)
    {
      number1.value = "0";
      number1.sign = '+';
    }
    else if(num[0]=='+' || num[0]=='-')
    {
      number1.sign = num[0];
      number1.value = num.substr(1,(num.length()-1));
    }
    else
    {
      number1.value = num;
      number1.sign = '+';
    }
  }

  struct number get_number()
  {
    return number1;
  }

  string get_value()
  {
    string s = "";
    if(number1.sign == '-')
    {
      s = string(1,number1.sign);
    }
    s = s.append(number1.value);
    return s;
  }

  int compare(BigInteger b1, BigInteger b2)
  {
    struct number bn1 = b1.get_number();
    struct number bn2 = b2.get_number();
    if(bn1.sign=='+' && bn2.sign=='-')
    {
      return 1;
    }
    if(bn1.sign=='-' && bn2.sign=='+')
    {
      return -1;
    }
    if(bn1.sign=='-' && bn2.sign=='-')
    {
      string val1 = bn1.value;
      string val2 = bn2.value;
      if(val1.length() > val2.length())
      {
        return -1;
      }
      if(val1.length() < val2.length())
      {
        return 1;
      }
      for(int i=0; i<val1.length(); i++)
      {
        int x = val1[i] - '0';
        int y = val2[i] - '0';
        if(x>y)
        {
          return -1;
        }
        else if(x<y)
        {
          return 1;
        }
      }
    }
    if(bn1.sign=='+' && bn2.sign=='+')
    {
      string val1 = bn1.value;
      string val2 = bn2.value;
      if(val1.length() < val2.length())
      {
        return -1;
      }
      if(val1.length() > val2.length())
      {
        return 1;
      }
      for(int i=0; i<val1.length(); i++)
      {
        int x = val1[i] - '0';
        int y = val2[i] - '0';
        if(x<y)
        {
          return -1;
        }
        else if(x>y)
        {
          return 1;
        }
      }
    }
    return 0;
  }

  string get_absolute_value()
  {
    return number1.value;
  }

  string reduce(string n1,string n2)
  {
    string res = "";
    int l = n1.length() - n2.length();
    for(int i=0; i<l; i++)
    {
      string zero = "0";
      n2 = zero.append(n2);
    }
    int borrow = 0;
    for(int i=(n1.length()-1); i>=0; i--)
    {
      int x = n1[i] - '0';
      int y = n2[i] - '0';
      x = x-borrow;
      int z = x-y;
      if(z<0)
      {
        borrow = 1;
        z = 10+z;
      }
      else
      {
        borrow = 0;
      }
      string temp = to_string(z);
      res = temp.append(res);
    }
    int t = 0;
    for(int i=0; i<res.length(); i++)
    {
        if(res[i]!='0')
        {
          break;
        }
        t++;
    }
    res = res.substr(t,(res.length()-t));
    if(res.empty())
    {
      res = "0";
    }
    return res;
  }

  BigInteger subtract(BigInteger num2)
  {
    struct number number2 = num2.get_number();
    char s1 = number1.sign;
    char s2 = number2.sign;
    BigInteger result;
    if((s1=='+' && s2=='-') || (s1=='-' && s2=='+'))
    {
      BigInteger tempb1 = BigInteger(get_absolute_value());
      BigInteger tempb2 = BigInteger(num2.get_absolute_value());
      BigInteger tempb3 = tempb1.add(tempb2);
      string res = tempb3.get_absolute_value();
      res = (string(1,s1)).append(res);
      result = BigInteger(res);
    }
    else
    {
      char r_s = '+';
      int c = compare(*this,num2);
      string n1 = get_absolute_value();
      string n2 = num2.get_absolute_value();
      if(c==0)
      {
        result = BigInteger();
      }
      else if(c==1)
      {
        r_s = '+';
        string res;
        if(s1=='-')
        {
          string temp = n1;
          n1 = n2;
          n2 = temp;
        }
        res = reduce(n1,n2);
        string r_s_s = string(1,r_s);
        res = r_s_s.append(res);
        result = BigInteger(res);
      }
      else
      {
        r_s = '-';
        string res;
        if(s1=='+')
        {
          string temp = n1;
          n1 = n2;
          n2 = temp;
        }
        res = reduce(n1,n2);
        string r_s_s = string(1,r_s);
        res = r_s_s.append(res);
        result = BigInteger(res);
      }
    }
    return result;
  }

  BigInteger add(BigInteger num2)
  {
    struct number number2 = num2.get_number();
    char s1 = number1.sign;
    char s2 = number2.sign;
    string n1 = number1.value;
    string n2 = number2.value;
    string result = "";
    BigInteger big_result;
    if((s1=='+' && s2=='+') || (s1=='-' && s2=='-'))
    {
      string zeros = "0";
      string zero = "0";
      if(n1.length() == n2.length())
      {
        n1 = zero.append(n1);
        zero = "0";
        n2 = zero.append(n2);
      }
      else if(n1.length() > n2.length())
      {
        int l1 = n1.length();
        int l2 = n2.length();
        int diff = l1-l2;
        for(int i=0; i<diff; i++)
        {
          zeros+='0';
        }
        n1 = zero.append(n1);
        n2 = zeros.append(n2);
      }
      else
      {
        int l1 = n1.length();
        int l2 = n2.length();
        int diff = l2-l1;
        for(int i=0; i<diff; i++)
        {
          zeros+='0';
        }
        n1 = zeros.append(n1);
        n2 = zero.append(n2);
      }
      int carry=0;
      for(int i=(n1.length()-1); i>=0; i--)
      {
        char a = n1[i];
        char b = n2[i];
        int x = a - '0';
        int y = b - '0';
        int sum = x+y+carry;
        string s = to_string(sum%10);
        carry = sum/10;
        result = s.append(result);
      }
      int t = 0;
      for(int i=0; i<result.length(); i++)
      {
          if(result[i]!='0')
          {
            break;
          }
          t++;
      }
      result = result.substr(t,(result.length()-t));
      if(result.empty())
      {
        result = "0";
      }
      string s = string(1,s1);
      big_result = BigInteger(s.append(result));
    }
    else
    {
      if(s1=='+')
      {
        BigInteger a = BigInteger(number1.value);
        BigInteger b = BigInteger(number2.value);
        big_result = a.subtract(b);
      }
      else
      {
        BigInteger a = BigInteger(number2.value);
        BigInteger b = BigInteger(number1.value);
        big_result = a.subtract(b);
      }
    }
    return big_result;
  }
};
int main()
{
  string x = "3124";
  string y = "-1119";
  BigInteger a = BigInteger(x);
  BigInteger b = BigInteger(y);
  BigInteger c = a.add(b);
  cout<<c.get_value()<<endl;
  return 0;
}
