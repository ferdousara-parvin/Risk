//#include <vector>
//#include "Orders.h"
//
//int main() {
//    OrdersList *list = new OrdersList();
//    Order *overToMove = new DeployOrder();
//    Order *orderToRemove = new BombOrder();
//    list->add(overToMove);
//    list->add(new AdvanceOrder(new Territory(), new Territory(), 10));
//    list->add(orderToRemove);
//    list->add(new BlockadeOrder());
//    list->add(new AirliftOrder());
//    list->add(new NegotiateOrder());
//
//    // Tests
//    cout << "-----------Original OrderList-----------" << endl;
//    cout << *list << endl;
//    cout << "-----------Test Move Deploy to 3rd place-----------" << endl;
//    list->move(overToMove, 2);
//    cout << *list << endl;
//    cout << "-----------Test Move Deploy to 1st place-----------" << endl;
//    list->move(overToMove, 0);
//    cout << *list << endl;
//    cout << "-----------Test Remove Bomb Order-----------" << endl;
//    list->remove(orderToRemove);
//    cout << *list << endl;
//    cout << "-----------Test Sorting-----------" << endl;
//    list->sortOrderListByPriority();
//    cout << *list << endl;
//}