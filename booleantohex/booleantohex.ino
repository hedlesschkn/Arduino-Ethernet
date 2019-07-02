byte binary=B1111;
char buffer[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Boolean to Hex");
  sprintf (buffer, "%02X", binary);
  Serial.print (buffer);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
