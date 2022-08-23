#include<bits/stdc++.h>
#include<windows.h>

using namespace std;

void GoToXY(int column, int line)
{
    // Create a COORD structure and fill in its members.
    // This specifies the new position of the cursor that we will set.
    COORD coord;
    coord.X = column;
    coord.Y = line;

    // Obtain a handle to the console screen buffer.
    // (You're just using the standard console, so you can use STD_OUTPUT_HANDLE
    // in conjunction with the GetStdHandle() to retrieve the handle.)
    // Note that because it is a standard handle, we don't need to close it.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Finally, call the SetConsoleCursorPosition function.
    if (!SetConsoleCursorPosition(hConsole, coord))
    {
        // Uh-oh! The function call failed, so you need to handle the error.
        // You can call GetLastError() to get a more specific error code.
        // ...
    }
}

void print_line(string str){
  int n=str.length();
  for(int i=0;i<n;i++){
    Sleep(1);//+ rand()%200);
    cout<<str[i];
  }
  cout<<endl;
}

void print_erase_line(string str){
  int n=str.length();
  for(int i=0;i<n;i++){
    Sleep(1);//+ rand()%200);
    cout<<str[i];
  }
  for(int i=0;i<n;i++){
    Sleep(1);//+ rand()%200);
    cout<<'\b'<<" "<<'\b' ;
  }
}

void print_square(){
  int x,y;
  cout<<"type side_length:";
  cin>>x;
  y=x;
  cout<<endl;
  for(int i=0;i<x;i++){
    for(int j=0;j<y;j++){
      cout<<"O " ;
    }
    cout<<endl;
  }
}

void delete_line(){
  cout << "\r"<<endl;
  // cout<<"\r                                      ";
}




void make_cicle(){
  // int r;
  // cout<<"type radius:";
  // cin>>r;
  // int x = r, y = 2*r + 1;
  // cout<<endl;
  int x=10,y=21;
  vector<string> circle(x+1);
  int x_mid=x>>1, y_mid=y>>1;

  for(int i=0;i<=x;i++)
    for(int j=0;j<y;j++)
      circle[i] = circle[i] + " ";
  
  int a=2, yl=y_mid, yr=y_mid;
  for(int i=0;i<=x;i++){
    circle[i][yl]='O';
    circle[i][yr]='O';
    yl -= a;
    yr += a;
    if(yl==0) a = -2;
    cout<<circle[i]<<endl;
  }

}

vector<pair<int,int>> get_points(vector<string> &circle){
  vector<pair<int,int>> points;
  int x = circle.size(),y=circle[0].length() - 1;
  int x_mid = x>>1 , y_mid = y>>1 ;
  int i = x_mid,j=0;
  while(i>0){
    points.push_back(make_pair(i,j));
    if(circle[i][j+1]!=' '){
      j++;
      continue;
    }
    if(circle[i-1][j]!=' '){
      i--;
      continue;
    }
    i--;
    j++;
  }
  points.push_back(make_pair(0,y_mid));
  for(int k=points.size()-2;k>=0;k--)
    points.push_back(make_pair(points[k].first, (y_mid<<1) - points[k].second ));
  for(int k=points.size()-2;k>0;k--)
    points.push_back(make_pair( (x_mid<<1) - points[k].first , points[k].second ));

  return points;
}

void rotate_circle(vector<string> &circle, vector<vector<pair<int,char>>> &upper_diagonals, vector<vector<pair<int,char>>> &lower_diagonals ,int len ){
  int x=circle.size(),y=circle[0].length() - 1,r=0;
  int x_mid = x>>1 , y_mid = y>>1, n=upper_diagonals.size() ,dig=0 ,xd,yd ,m=y ;
  int l = 0, a=1, i=n;
  int t;
  if(x_mid<=10) t=40;
  else if(x_mid<=20) t=25;
  else t=10;

  bool going_right = true;
  while(1){
      l++;
      if(going_right){
        if(i>=n)  i=0;
        
        for(int j=0;j<x;j++)
          circle[j] = ' ' + circle[j];
      }else{
        if(i<0) i=n-1;
        
        for(int j=0;j<x;j++)
          circle[j] = circle[j].substr(1,500);
      }
      y_mid += a;
      for(auto point : upper_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid - xd][y_mid + yd] = circle[x_mid + xd][y_mid - yd] =  point.second;
        // cout<<xd<<" "<<yd<<" | ";
      }
      for(auto point : lower_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid + xd][y_mid + yd] = circle[x_mid - xd][y_mid - yd] = point.second;
        // cout<<xd<<" "<<yd<<" | ";
      }
      circle[x_mid][y_mid] = '+';
      GoToXY(0,8);
      for(int j=0;j<x;j++){
        cout<<circle[j]<<endl;
      }

      circle[x_mid][y_mid] = ' ';
      for(auto point : upper_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid - xd][y_mid + yd] = circle[x_mid + xd][y_mid - yd] = ' ';
        // cout<<xd<<" "<<yd<<" | ";
      }
      for(auto point : lower_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid + xd][y_mid + yd] = circle[x_mid - xd][y_mid - yd] = ' ';
        // cout<<xd<<" "<<yd<<" | ";
      }
      Sleep(t);
      if(l==len){
        going_right = !going_right;
        a = -a;
        l=0;
        r++;
        if(r==6)  break;
      }
      i += a;

  }
}

void rotate_circle_2(vector<string> &circle,int len ){
  int x=circle.size(),y=circle[0].length() - 1,r=0;
  int x_mid = x>>1 , y_mid = y>>1,dig=0 ,xd,yd ,m=y ;
  int l = 0, a=1 , d=0;
  int t;
  if(x_mid<=10) t=40;
  else if(x_mid<=20) t=25;
  else t=10;

  bool going_right = true;
  vector<pair<int,int>> points = get_points(circle);

  while(1){
      l++;

      GoToXY(0,8);
      for(int j=0;j<x;j++){
        cout<<circle[j]<<endl;
      }

      if(going_right){
        char last = circle[points[points.size()-1].first][points[points.size()-1].second + d];
        for(int i=points.size()-1;i>0;i--)
          circle[points[i].first][points[i].second + d] = circle[points[i-1].first][points[i-1].second + d];
        circle[points[0].first][points[0].second + d] = last;
        for(int j=0;j<x;j++)
          circle[j] = ' ' + circle[j];
        d++;
      }else{
        char last = circle[points[0].first][points[0].second + d];
        for(int i=0; i<points.size()-1 ;i++)
          circle[points[i].first][points[i].second + d] = circle[points[i+1].first][points[i+1].second + d];
        circle[points[points.size()-1].first][points[points.size()-1].second + d] = last;
        for(int j=0;j<x;j++){
          circle[j] = circle[j].substr(1,500);
        }
        d--;
      }
      // y_mid += a;


      Sleep(t);

      if(l==len){
        going_right = !going_right;
        l=0;
        r++;
        if(r==6)  break;
      }

  }
}

void rotate_circle_3(vector<string> &circle, vector<vector<pair<int,char>>> &upper_diagonals, vector<vector<pair<int,char>>> &lower_diagonals ,int len ){
  int x=circle.size(),y=circle[0].length() - 1,r=0;
  int x_mid = x>>1 , y_mid = y>>1, n=upper_diagonals.size() ,dig=0 ,xd,yd ,m=y ;
  int l = 0, a=1 , d=0 , i=n;
  int t;
  if(x_mid<=10) t=40;
  else if(x_mid<=20) t=25;
  else t=10;

  bool going_right = true;
  vector<pair<int,int>> points = get_points(circle);

  while(1){
      l++;
      if(going_right){
        if(i==n)  i=0;
      }else{
        if(i<0) i=n-1;
      }
      for(auto point : upper_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid - xd][y_mid + yd] = circle[x_mid + xd][y_mid - yd] =  point.second;
        // cout<<xd<<" "<<yd<<" | ";
      }
      for(auto point : lower_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid + xd][y_mid + yd] = circle[x_mid - xd][y_mid - yd] = point.second;
        // cout<<xd<<" "<<yd<<" | ";
      }
      circle[x_mid][y_mid] = '+';


      GoToXY(0,8);
      for(int j=0;j<x;j++){
        cout<<circle[j]<<endl;
      }

      circle[x_mid][y_mid] = ' ';
      for(auto point : upper_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid - xd][y_mid + yd] = circle[x_mid + xd][y_mid - yd] = ' ';
        // cout<<xd<<" "<<yd<<" | ";
      }
      for(auto point : lower_diagonals[i]){
        xd = point.first/m, yd = point.first%m;
        circle[x_mid + xd][y_mid + yd] = circle[x_mid - xd][y_mid - yd] = ' ';
        // cout<<xd<<" "<<yd<<" | ";
      }
      y_mid += a;

      if(going_right){

        char last = circle[points[points.size()-1].first][points[points.size()-1].second + d];
        for(int i=points.size()-1;i>0;i--)
          circle[points[i].first][points[i].second + d] = circle[points[i-1].first][points[i-1].second + d];
        circle[points[0].first][points[0].second + d] = last;
        
        for(int j=0;j<x;j++)
          circle[j] = ' ' + circle[j];
        d++;
      }else{

        char last = circle[points[0].first][points[0].second + d];
        for(int i=0; i<points.size()-1 ;i++)
          circle[points[i].first][points[i].second + d] = circle[points[i+1].first][points[i+1].second + d];
        circle[points[points.size()-1].first][points[points.size()-1].second + d] = last;

        for(int j=0;j<x;j++)
          circle[j] = circle[j].substr(1,500);
        d--;
      }
      // y_mid += a;


      Sleep(t);
      // usleep(30)

      if(l==len){
        going_right = !going_right;
        a = -a;
        l=0;
        r++;
        if(r==8)  break;
      
 }     i+=a;
  }
}


void make_diagonals(vector<string> &circle, vector<vector<pair<int,char>>> &upper_diagonals, vector<vector<pair<int,char>>> &lower_diagonals ){
  int x=circle.size(),y=circle[0].length() - 1;
  int x_mid = x>>1 , y_mid = y>>1, n=0 ;
  int m = y;
  // if(x_mid&1) last_diag = (x_mid>>1) - 1;
  // else        last_diag = (x_mid>>1) - 1;
  vector<pair<int,char>> cur_diagonal;

  for(int i=1;i<x_mid;i++)
    cur_diagonal.push_back(make_pair( i*m , '|' ));

  upper_diagonals.push_back(cur_diagonal); // vertiical diagonal completed

  int a=1;
  while(circle[x_mid - a][y_mid + a]==' ' && circle[x_mid - a -1][y_mid + a]==' '&& circle[x_mid - a][y_mid + a + 1]==' '){
    n++;
    a++;
  }
  // cout<<"here+"<<n<<endl;
  if(n&1) n = n>>1;
  else    n = (n>>1) - 1; // n-maxslanting diagonal

  int mid_ds=0,x1,y1;

  for(int i=1;i<=n;i++){     // vertical to mid slanting diagonal
    // cout<<"$"<<endl;
    vector<pair<int,char>> cur_diagonal_1;
    for(int j=1;j<=i;j++){
      cur_diagonal_1.push_back(make_pair(j*m + j , '/'));
    }
    int k = 2*i + 1;
    x1=k , y1=k, mid_ds=0;
    while(circle[x_mid - x1][y_mid + y1]==' '){
      mid_ds++;
      x1++;
    }
    x1 = i+1;
    while(mid_ds--){
      cur_diagonal_1.push_back(make_pair(x1*m + i+1 ,'|' ));
      x1++;
    }
    x1--;
    // cout<<i;
    for(int j=1;j<=i;j++){
      cur_diagonal_1.push_back(make_pair((j + x1)*m + (j + i+1) , '/'));
    }
    upper_diagonals.push_back(cur_diagonal_1);
  }

  x1=1,y1=1;
  vector<pair<int,char>> slant_diagonal;
  while(circle[x_mid - x1][y_mid + y1]==' ' && circle[x_mid - x1 - 1][y_mid + y1]==' ' && circle[x_mid - x1][y_mid + y1 + 1]==' ' ){
    slant_diagonal.push_back(make_pair(x1*m + y1,'/'));
    x1++;
    y1++;
  }
  upper_diagonals.push_back(slant_diagonal);

  for(int i=n;i>0;i--){
    vector<pair<int,char>> cur_diagonal_2;
    for(int j=1;j<=i;j++){
      cur_diagonal_2.push_back(make_pair(j*m + j , '/'));
    }
    int k = 2*i + 1;
    x1=k , y1=k, mid_ds=0;
    while(circle[x_mid - x1][y_mid + y1]==' '){
      mid_ds++;
      y1++;
    }
    x1=i+1, y1 = i+1;
    while(mid_ds--){
      cur_diagonal_2.push_back(make_pair(x1*m + y1 ,'-' ));
      y1++;
    }
    y1--;
    for(int j=1;j<=i;j++){
      cur_diagonal_2.push_back(make_pair((j + x1)*m + (j + y1) , '/'));
    }
    upper_diagonals.push_back(cur_diagonal_2);

  }

  vector<pair<int,char>> hor_diagonal;
  for(int j=1;j<y_mid;j++)
    hor_diagonal.push_back(make_pair(j , '-'));
  lower_diagonals.push_back(hor_diagonal);


  for(int i=upper_diagonals.size()-1 ; i>0 ;i--){
    vector<pair<int,char>> lower_d;
    for(int j=0;j<upper_diagonals[i].size();j++){
      char cur = (upper_diagonals[i][j].second=='/') ? '\\' : upper_diagonals[i][j].second;
      lower_d.push_back(make_pair(upper_diagonals[i][j].first,cur));
    }
    lower_diagonals.push_back(lower_d);
  }

  // for(auto dg:upper_diagonals){
  //   for(auto point : dg){
  //     int xd = point.first/m, yd = point.first%m;
  //     circle[x_mid - xd][y_mid + yd] = point.second;
  //     // cout<<xd<<" "<<yd<<" | ";
  //   }
  // }
  // for(auto dg:lower_diagonals){
  //   for(auto point : dg){
  //     int xd = point.first/m, yd = point.first%m;
  //     circle[x_mid + xd][y_mid + yd] = point.second;
  //     // cout<<xd<<" "<<yd<<" | ";
  //   }
  // }
  // cout<<"here";

}


vector<string> draw_circle(){
  int radius,l;
  cout<<"Type Radius:";
  cin>>radius;
  if(radius&1)  radius--;
  while(1){
    cout<<"Type length:";
    cin>>l;
    break;
    if(l>(radius<<1))  break;
    else cout<<"length should be greater than diameter. ";
  }
  int x = (radius<<1), y = (radius<<2) + 1;
  vector<string> circle(x+1);

  for(int i=0;i<=x;i++)
    for(int j=0;j<=y;j++)
      circle[i] = circle[i] + " ";

  circle[0][(y>>1)] = circle[radius][0] = circle [x][(y>>1)] = circle[radius][y-1] = 'O';

  queue<pair<int,int>> q;
  int x1,y1=(y>>1)-1,cnt_x=radius,cnt_y=y>>1,r2=radius*radius;
  // cout<<cnt_x<<"  "<<cnt_y<<" "<<r2<<endl;
  while(y1>0){
    int xs = sqrt(abs(4*r2 - (cnt_y - y1)*(cnt_y-y1)));
    xs=xs>>1;
    x1 = cnt_x - xs;
    pair<int,int> cur = make_pair(x1,y1);
    q.push(cur);
    circle[x1][y1] = circle[x1][2*cnt_y - y1] = circle[x-x1][y1] = circle[x-x1][2*cnt_y - y1] = 'O' ;
    y1--;
    // cout<<x1<<" | ";
  }
  x1=radius-1;
  while(x1>0){
    int ys = (2*sqrt(abs(r2 - (cnt_x - x1)*(cnt_x - x1))));
    y1 = cnt_y - ys;
    // if()
    pair<int,int> cur = make_pair(x1,y1);
    q.push(cur);
    circle[x1][y1]= circle[x1][2*cnt_y - y1] = circle[x-x1][y1] = circle[x-x1][2*cnt_y - y1] = 'O';
    x1--;
    // cout<<y1<<" | ";
  }
  vector<vector<pair<int,char>>> upper_diagonals;
  vector<vector<pair<int,char>>> lower_diagonals;

  make_diagonals(circle,upper_diagonals,lower_diagonals);

  rotate_circle(circle,upper_diagonals,lower_diagonals,l);
  // for(int i=0;i<=x;i++){
  //   cout<<circle[i]<<endl;
  //   Sleep(10);
  // }

  return circle;
}


vector<string> draw_circle_2(){
  srand(time(0));
  int radius,l;
  cout<<"Type Radius:";
  cin>>radius;
  if(radius&1)  radius--;
  while(1){
    cout<<"Type length:";
    cin>>l;
    break;
    if(l>(radius<<1))  break;
    else cout<<"length should be greater than diameter. ";
  }
  int x = (radius<<1), y = (radius<<2) + 1 , ascii_val=rand()%80;
  vector<string> circle(x+1);

  for(int i=0;i<=x;i++)
    for(int j=0;j<=y;j++)
      circle[i] = circle[i] + " ";

  circle[0][(y>>1)] = circle[radius][0] = circle [x][(y>>1)] = circle[radius][y-1] = '@';

  int x1,y1=(y>>1)-1,cnt_x=radius,cnt_y=y>>1,r2=radius*radius ;
  // cout<<cnt_x<<"  "<<cnt_y<<" "<<r2<<endl;
  while(y1>0){
    ascii_val+=2;
    if(ascii_val>89)  ascii_val = 1;
    int xs = sqrt(abs(4*r2 - (cnt_y - y1)*(cnt_y-y1)));
    xs=xs>>1;
    x1 = cnt_x - xs;
    circle[x1][y1] = circle[x1][2*cnt_y - y1] = circle[x-x1][y1] = circle[x-x1][2*cnt_y - y1] = ' ' + ascii_val;
    // circle[x1][y1] =  'A' + ascii_val ;
    // circle[x1][2*cnt_y - y1] =  'A' + ascii_val + 7 ;
    // circle[x-x1][y1] =  'A' + ascii_val + 14;
    // circle[x-x1][2*cnt_y - y1] = 'A' + ascii_val + 21 ;
    y1--;
    // cout<<x1<<" | ";
  }
  x1=radius-1;
  while(x1>0){
    ascii_val+=2;
    if(ascii_val>89)  ascii_val = 2;
    int ys = (2*sqrt(abs(r2 - (cnt_x - x1)*(cnt_x - x1))));
    y1 = cnt_y - ys;
    // if()
    circle[x1][y1] = circle[x1][2*cnt_y - y1] = circle[x-x1][y1] = circle[x-x1][2*cnt_y - y1] = ' ' + ascii_val ;
    // circle[x1][y1] =  'A' + ascii_val ;
    // circle[x1][2*cnt_y - y1] =  'A' + ascii_val + 7 ;
    // circle[x-x1][y1] =  'A' + ascii_val + 14;
    // circle[x-x1][2*cnt_y - y1] = 'A' + ascii_val + 21 ;

    x1--;
    // cout<<y1<<" | ";
  }

  rotate_circle_2(circle,l);
  // for(int i=0;i<=x;i++){
  //   cout<<circle[i]<<endl;
  //   Sleep(10);
  // }

  return circle;
}

vector<string> draw_circle_3(){
  srand(time(0));
  int radius,l;
  cout<<"Type Radius:";
  cin>>radius;
  if(radius&1)  radius--;
  while(1){
    cout<<"Type length:";
    cin>>l;
    break;
    if(l>(radius<<1))  break;
    else cout<<"length should be greater than diameter. ";
  }
  int x = (radius<<1), y = (radius<<2) + 1 , ascii_val=rand()%6;
  vector<string> circle(x+1);

  for(int i=0;i<=x;i++)
    for(int j=0;j<=y;j++)
      circle[i] = circle[i] + " ";

  circle[0][(y>>1)] = circle[radius][0] = circle [x][(y>>1)] = circle[radius][y-1] = '@';

  int x1,y1=(y>>1)-1,cnt_x=radius,cnt_y=y>>1,r2=radius*radius ;
  // cout<<cnt_x<<"  "<<cnt_y<<" "<<r2<<endl;
  while(y1>0){
    int xs = sqrt(abs(4*r2 - (cnt_y - y1)*(cnt_y-y1)));
    xs=xs>>1;
    x1 = cnt_x - xs;
    circle[x1][y1] =  'A' + ascii_val ;
    circle[x1][2*cnt_y - y1] =  'A' + ascii_val + 7 ;
    circle[x-x1][y1] =  'A' + ascii_val + 14;
    circle[x-x1][2*cnt_y - y1] = 'A' + ascii_val + 21 ;
    y1--;
    // cout<<x1<<" | ";
  }
  x1=radius-1;
  while(x1>0){
    int ys = (2*sqrt(abs(r2 - (cnt_x - x1)*(cnt_x - x1))));
    y1 = cnt_y - ys;
    circle[x1][y1] =  'A' + ascii_val + 3 ;
    circle[x1][2*cnt_y - y1] =  'A' + ascii_val + 4 ;
    circle[x-x1][y1] =  'A' + ascii_val + 11;
    circle[x-x1][2*cnt_y - y1] = 'A' + ascii_val + 19 ;

    x1--;
    // cout<<y1<<" | ";
  }

  rotate_circle_2(circle,l);
  // for(int i=0;i<=x;i++){
  //   cout<<circle[i]<<endl;
  //   Sleep(10);
  // }

  return circle;
}

vector<string> draw_circle_4(){
  srand(time(0));
  int radius,l;
  cout<<"Type Radius:";
  cin>>radius;
  if(radius&1)  radius--;
  while(1){
    cout<<"Type length:";
    cin>>l;
    break;
    if(l>(radius<<1))  break;
    else cout<<"length should be greater than diameter. ";
  }
  int x = (radius<<1), y = (radius<<2) + 1 , ascii_val=rand()%6;
  vector<string> circle(x+1);

  for(int i=0;i<=x;i++)
    for(int j=0;j<=y;j++)
      circle[i] = circle[i] + " ";

  circle[0][(y>>1)] = circle[radius][0] = circle [x][(y>>1)] = circle[radius][y-1] = '@';

  int x1,y1=(y>>1)-1,cnt_x=radius,cnt_y=y>>1,r2=radius*radius ;
  // cout<<cnt_x<<"  "<<cnt_y<<" "<<r2<<endl;
  while(y1>0){
    int xs = sqrt(abs(4*r2 - (cnt_y - y1)*(cnt_y-y1)));
    xs=xs>>1;
    x1 = cnt_x - xs;
    circle[x1][y1] =  'A' + ascii_val ;
    circle[x1][2*cnt_y - y1] =  'A' + ascii_val + 7 ;
    circle[x-x1][y1] =  'A' + ascii_val + 14;
    circle[x-x1][2*cnt_y - y1] = 'A' + ascii_val + 21 ;
    y1--;
    // cout<<x1<<" | ";
  }
  x1=radius-1;
  while(x1>0){
    int ys = (2*sqrt(abs(r2 - (cnt_x - x1)*(cnt_x - x1))));
    y1 = cnt_y - ys;
    circle[x1][y1] =  'A' + ascii_val + 3 ;
    circle[x1][2*cnt_y - y1] =  'A' + ascii_val + 4 ;
    circle[x-x1][y1] =  'A' + ascii_val + 11;
    circle[x-x1][2*cnt_y - y1] = 'A' + ascii_val + 19 ;

    x1--;
    // cout<<y1<<" | ";
  }
  vector<vector<pair<int,char>>> upper_diagonals;
  vector<vector<pair<int,char>>> lower_diagonals;

  make_diagonals(circle,upper_diagonals,lower_diagonals);

  rotate_circle_3(circle,upper_diagonals,lower_diagonals,l);

  // for(int i=0;i<=x;i++){
  //   cout<<circle[i]<<endl;
  //   Sleep(10);
  // }

  return circle;
}

int main(){
  system("cls");
  // cout<<endl;
  // make_cicle();
  // draw_circle(); 
  // draw_circle_2(); 
  // draw_circle_3(); 
  draw_circle_4(); 

  // print_square();
  getchar();
  return 0;
}


    // for(int j=0;j<10000000;j++) ;
    // // sleep(10);






