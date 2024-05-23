#define LDR_PIN A0

#define LED_N   3

const int led_pins[LED_N] = {2, 3, 4};//, 5};
const int soglie[LED_N] = {70, 220, 550};//, 900};

struct {
  int val{0};
} input_data;

void input(void){
  input_data.val = analogRead(LDR_PIN);
}

typedef int state_t;

#define STATE_BASE          ((state_t)0)
#define STATE_MAX           ((state_t)(STATE_BASE + LED_N))

#define DEFAULT_STATE   STATE_BASE

state_t state = DEFAULT_STATE;

void stato(void){
  if (STATE_BASE <= state <= STATE_MAX){
    int s0 = 0;
    for (int i = STATE_BASE; i < STATE_MAX; i++){
      int s1 = soglie[i - STATE_BASE];
      if (s0 <= input_data.val && input_data.val < s1){
        state = i;
        return;
      }
      s0 = s1;
    }
    state = STATE_MAX;
  }
}

void output(void){
  static state_t last_state = DEFAULT_STATE;
  if (state != last_state){
    for(int i = 0; i < LED_N; i++){
      digitalWrite(led_pins[i], LOW);
    }
    for (int i = STATE_BASE + 1; i <= state; i++){
      digitalWrite(led_pins[i - STATE_BASE - 1], HIGH);
    }
    last_state = state;
  }
}

void setup() {
  pinMode(LDR_PIN, INPUT);
  for (int i = 0; i < LED_N; i++){
    pinMode(led_pins[i], OUTPUT);
  }
}

void loop() {
  input();
  stato();
  output();
  delay(100);
}
