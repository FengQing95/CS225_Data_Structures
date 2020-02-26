// your code here
#include "q5.h"
#include "Food.h"
void increase_quantity(Food * food){
int num = food->get_quantity();
food->set_quantity(num + 1);
}
