#include <mbed.h>
#include <rtos.h>
#include <mbed_events.h>
#include <C12832.h>
Serial pc(USBTX, USBRX);

DigitalOut red(LED1,1);
void flash(void){
    red = !red;
}

DigitalOut green(LED2,1);
void blink(void){
    pc.printf("This is not in an ISR so I can do long (time) operations\n");
    green = !green;
}
Thread worker;

EventQueue queue ;

// InterruptIn sw(SW2);
// int main() {
//    sw.rise(flash); /* executes as an ISR */
//    sw.fall(queue.event(blink));
//    worker.start(callback(&queue, &EventQueue::dispatch_forever ));
//    while(1){}
// }

C12832 lcd(D11, D13, D12, D7, D10);
void updateLCD(void){
  lcd.locate(0, 0);
  lcd.printf("Hello or something");
  wait_ms(500);
  lcd.cls();
}
void clearlcd(void){
  wait_ms(500);
  lcd.cls();
}

int main(){
    // queue.call_every(1000,clearlcd);
    queue.call_every(1000,updateLCD);
    queue.dispatch_forever();

  }
