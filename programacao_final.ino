// Define a porta digital para o pino echo do sensor como sendo a 2.
#define echoPin 2      

// Define a porta digital para o pino trig do sensor como sendo a 3.
#define trigPin 3      

// Define a porta digital para o pino do buzzer como sendo a 5.
#define buzzerPin 5    

// Define um valor de 125 milissegundos para a lógica de tempo dos bips.
#define tempo 125       



// Define o maior alcance que o sensor irá detectar.
int distMax = 50;       

// Define o alcance médio que o sensor irá detectar.
int distMed = 30;  

// Define o menor alcance que o sensor irá detectar.
int distMin = 15;       

// Cria uma variável para armazenar os valores da distância detectada.
int distancia;      

// Cria uma variável para armazenar o valor da duração de um pulso HIGH e LOW de uma porta digital.
long duracao;       



// Aqui no setup é feita a configuração de sensores e atuadores
void setup() {      
  // Define o pino echo como INPUT - entrada de dados
  pinMode(echoPin, INPUT);  
  // Define o pino trig como OUTPUT - saída de dados
  pinMode(trigPin, OUTPUT); 
  // Define o pino do buzzer como OUTPUT - saída de dados
  pinMode(buzzerPin, OUTPUT); 
  // Configura o monitor serial com 9600 bits por segundo
  Serial.begin(9600);  
}

 // Aqui no loop é onde colocamos tudo para funcionar
void loop() {    

  // Chama a função de medir a distância
  medirDistancia();  

  // Inicia as condições para os bips
  // Se a distância for menor ou igual que o alcance mínimo, liga o buzzer com 3000Mhz de freqûencia
  // Desligando e ligando a cada 62,5 milissegundos 
  if (distancia <= distMin){
    tone(buzzerPin, 3000);
    delay(tempo/2);
    noTone(buzzerPin);
    delay(tempo/2);
  }

  // Caso a distancia esteja entre o alcance mínimo e o médio, liga o buzzer com 6000Mhz de freqûencia
  // Desligando e ligando a cada 125 milissegundos
  else if (distancia > distMin && distancia <= distMed){
    tone(buzzerPin, 6000);
    delay(tempo);
    noTone(buzzerPin);
    delay(tempo);
  }

  // Caso a distancia esteja entre o alcance médio e o máximo, liga o buzzer com 10000Mhz de freqûencia
  // Desligando e ligando a cada 250 milissegundos
  else if (distancia > distMed && distancia <= distMax){
    tone(buzzerPin, 10000);
    delay(tempo*2);
    noTone(buzzerPin);
    delay(tempo*2);
  }

  // Caso não aconteça nenhuma das coisas acima, não irá emitir nenhum som
  else{
    noTone(buzzerPin);
  }
}

// Cria a função de medir a distância
int medirDistancia(){
  
  // Essa sequência de comandos fazem um pulo HIGH e LOW na porta digital do echo para receber
  // a onda sonora disparada pelo trig
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracao = pulseIn(echoPin, HIGH);
  
  // Define a distância detectada como sendo:
  // duração do pulso X velocidade do som no ar em centimetros por microssegundo
  // e no final divide por dois, pois o valor adquirido sem a divisão é o de ida e volta da onda sonora
  // e queremos apenas a distancia.
  distancia = duracao * 0.034 / 2;
  
  // Por fim, exibe a distância no monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");  
  delay(25);
}