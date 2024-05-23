#define LDR_PIN A0
#define LED_PIN 13

#define SOGLIA          (512)

struct {
  int val{0};
} input_data;

void input(void){
  input_data.val = analogRead(LDR_PIN);
}

typedef int state_t;
#define OFF_STATE       ((state_t)0)
#define ON_STATE        ((state_t)1)

#define DEFAULT_STATE   OFF_STATE

state_t state = DEFAULT_STATE;

void stato(void){
  if(input_data.val < SOGLIA){
    state = ON_STATE;
  } else {
    state = OFF_STATE;
  }
}

void output(void){
  static state_t last_state = DEFAULT_STATE;
  if (state != last_state){
    if (state == OFF_STATE){
      digitalWrite(LED_PIN, LOW);
    } else if (state == ON_STATE){
      digitalWrite(LED_PIN, HIGH);
    }
    last_state = state;
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  input();
  stato();
  output();
}
