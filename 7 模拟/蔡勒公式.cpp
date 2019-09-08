// 适用于1582年10月15日之后, 因为罗马教皇格里高利十三世在这一天启用新历法
// 蔡勒公式：给定年月日，得到当天是星期几
int Weekday(int year,int month,int day)
{
    if(month == 1 || month == 2) {
        month += 12;
        year--;
    }
    int c = year / 100;
    int y = year % 100;
    int m = month;
    int d = day;
    int w = c / 4 - 2 * c + y + y / 4 + 26 * (m + 1) / 10 + d - 1;
    if(w < 0)
        return (w + (-w / 7 + 1) * 7) % 7;
    return w % 7;
}
vector<string> s = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
