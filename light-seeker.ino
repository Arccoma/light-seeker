
/*
  빛 추적기 
  빛의 밝기 변화에 따른 cds sensor의 저항값 변화를 이용.
  상하, 좌우로 대칭을 이루어 배치된 2쌍의 센서의 아날로그 입력값을 비교.
  한 쌍의 센서의 입력의 차이가 일정 수준 이상일 경우 그 차이를 줄이는 방향으로 모터 회전.
  차이가 일정 수준 이하일 경우 기구는 빛을 정면으로 바라보게 됨.
  기구의 상하/좌우 회전범위는 마이크로 스위치로 제한.

  light-seeker
  
  using 4 cds sensors(input) and 4 realays(output)
  control 2 dc motor(actuator)
  this device seeking light just like a sunflower.
   
  modified  2013/7/31
  by Arccoma
  modifided 2022/6/1
  by Arccoma
  This code is in the public domain. 
*/

// cds sensor Analog input
#define EastPin A0
#define WestPin A1
#define SouthPin A2
#define NorthPin A3

#define DELTA 90 /*  좌우/상하 밝기 차이 기준(절대값). 
 한쌍의 아날로그 입력 차이가 이 값 이상이면 모터 동작.
 장치가 놓이는 장소의 조도에 따라 적당한 값으로 설정한다.
 장치가 너무 민감하게 반응하는 경우 숫자를 크게 한다.
 
 테스트 환경1: 햇빛이 들지 않는 사무실 형광등 조명환경 DELTA 70
 테스트 환경2:  DELTA 50
 테스트 환경3:  DELTA 90  
*/

// output
int realyEAST = 3;  
int realyWEST = 4;  
int realySOUTH = 5;  
int realyNORTH = 6;

int EastValue = 0;      int WestValue = 0;     int E_W_delta = 0;
int SouthValue = 0;     int NorthValue = 0;    int S_N_delta = 0;

void setup() {
  Serial.begin(9600);
  pinMode(realyEAST, OUTPUT ); 
  pinMode(realyWEST, OUTPUT );
  pinMode(realySOUTH, OUTPUT ); 
  pinMode(realyNORTH, OUTPUT );
}

void loop(){ 
  EastValue = analogRead(EastPin);  
  WestValue = analogRead(WestPin);  
  SouthValue = analogRead(SouthPin);  
  NorthValue = analogRead(NorthPin); 
  
  ////////////////////////////////////////////////////////////////////////////////
  // 동쪽 센서가 감도가 서쪽 센서보다 조금 민감한듯 하다.
  // 동쪽 센서 값을 조금 낮춰준다.
  E_W_delta = EastValue - WestValue - 70;// this one pair of cds's sensitivity is not equal.
  if ( E_W_delta > DELTA || E_W_delta < -DELTA )
  {
    if ( EastValue > WestValue )
    {
      Serial.print("Moving To East"); Serial.println();
      digitalWrite(realyWEST, LOW);   // West relay OFF   First OFF
      digitalWrite(realyEAST, HIGH);  // East relay ON    Second ON      inter rock

    }
    if ( EastValue < WestValue )
    {
      Serial.print("Moving To West"); Serial.println();
      digitalWrite(realyEAST, LOW);   // East realy OFF   First OFF
      digitalWrite(realyWEST, HIGH);  // West realy ON    Second ON       inter rock
    
    }
  }
  else
  { 
    digitalWrite(realyEAST, LOW);
    digitalWrite(realyWEST, LOW); 
    Serial.print("STOP"); Serial.println();
  }
  
   
  Serial.print("       East : "); Serial.print(EastValue);
  Serial.print("       West : "); Serial.print(WestValue);
  Serial.print("       delta: "); Serial.print(E_W_delta);
  Serial.println();
  
  //////////////////////////////////////////////////////////////////////////////////////

   S_N_delta = SouthValue - NorthValue;
  if ( S_N_delta > DELTA || S_N_delta < -DELTA )
  {
    if ( SouthValue > NorthValue )
    {
      Serial.print("Moving To South"); Serial.println();
      digitalWrite(realyNORTH, LOW);   // North relay OFF   First OFF
      digitalWrite(realySOUTH, HIGH);  // South relay ON    Second ON
    }
    if ( NorthValue > SouthValue  )
    {
      Serial.print("Moving To North"); Serial.println();
      digitalWrite(realySOUTH, LOW);   // South realy OFF   First OFF
      digitalWrite(realyNORTH, HIGH);  // North realy ON    Second ON
    }
  }
  else
  {
    digitalWrite(realySOUTH, LOW);
    digitalWrite(realyNORTH , LOW);
    Serial.print("STOP"); Serial.println();
  }
  Serial.print("       South : "); Serial.print(SouthValue);
  Serial.print("       North : "); Serial.print(NorthValue);
  Serial.print("       delta: "); Serial.print(S_N_delta);
  Serial.println();
  
  delay(50);
}
