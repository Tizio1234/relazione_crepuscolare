#define LDR_PIN A0

struct {
  int val{0};
} input_data;

void input(void){
  input_data.val = analogRead(LDR_PIN);
}

typedef int state_t;
#define DEFAULT_STATE   ((state_t)0)

state_t state = DEFAULT_STATE;

void stato(void){
  if (state == DEFAULT_STATE){
    Serial.print("A0 LDR val: ");
    Serial.println(input_data.val);
    delay(1000);
  }
}

void output(void){}

void setup() {
  Serial.begin(115200);
}

void loop() {
  input();
  stato();
  output();
}
