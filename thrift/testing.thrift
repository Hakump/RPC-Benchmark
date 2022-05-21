
struct IntMessage{
    1: i32 num = 1717
}

struct DoubleMessage{
    1: double num = 10.9191
}

struct StringMessage{
    1: string str,
}

const map<string,string> MAPCONSTANT = {'hello':'world', 'goodnight':'moon'}

const string STRMSG = "short message"


struct ShortMessage{
  1: i32 num1 = 0,
  2: double num2 = 0,
  3: string str,
}

struct LargeMessage{
  1: string string1,
  2: i32 size,
  3: list<i32> ints,
  4: list<double> doubles,
  5: list<bool> bools,
}

struct Lists{
    1: list<LargeMessage> numbers = [],
}

service ThriftMessage {
  i32 sendInt(1: IntMessage intMsg),
  string sendStr(1: StringMessage strMsg),
  double sendDouble(1: DoubleMessage doubleMsg),
  ShortMessage sendShortMsg(1: ShortMessage srtMsg),
  LargeMessage sendLargeMsg(1: LargeMessage lrgMsg),
  void ping()
}
