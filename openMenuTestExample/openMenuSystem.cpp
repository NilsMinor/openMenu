#include "openMenu.h"

MenuSystem::MenuSystem       (String _name) {
   menuSystemName = _name;
   menuQuantity   = 0;
   selectCounter  = 0;
   printMenuSystem ( );
}

int MenuSystem::addMenu          (Menu *m, void (*_menuCallback)(void)) {
  
  listMenu = (Menu**) realloc (listMenu, 
                              (menuQuantity+1) * sizeof(Menu*)); // reallocate listMenu array,
  if (listMenu!=NULL) {
    listMenu [menuQuantity++]   = m;
    m->addCallback (_menuCallback);
    return menuQuantity;
   }
   else {
     Serial.println ("Error (re)allocating memory");
     return NULL;
   }
}
int MenuSystem::addMenu          (Menu *m) {
  
  listMenu = (Menu**) realloc (listMenu, 
                              (menuQuantity+1) * sizeof(Menu*)); // reallocate listMenu array,
  if (listMenu!=NULL) {
    listMenu [menuQuantity++]   = m;
    return menuQuantity;
   }
   else {
     Serial.println ("Error (re)allocating memory");
     return NULL;
   }
}
void MenuSystem::printMenuSystem (void) {
  Serial.println ("menuQuantity:    "); Serial.println(menuQuantity);
  Serial.print   ("selectCounter:   "); Serial.println(selectCounter);
  Serial.println ("");
  
  Serial.print ("--> "); Serial.println(menuSystemName);
  
  for (int i = 0; i != menuQuantity; i++) {
    Serial.print("----> "); Serial.print (listMenu[i]->getName ( ));
    
    if (listMenu [i]->isSelected ( )) Serial.print ("     (selected)");
      
    Serial.println("");
  }
}
String MenuSystem::getName (void) {
  return menuSystemName;
}
void MenuSystem::next       (void) {
  if (selectCounter < menuQuantity-1) {
    listMenu [selectCounter]->unselect ( );  // unselect previous
    listMenu [++selectCounter]->select ( );    // select next 
  }
  
}
void MenuSystem::prev       (void) {
  if (selectCounter > 0) {
    listMenu [selectCounter]->unselect ( );  // unselect previous 
    listMenu [--selectCounter]->select ( );    // select next 
  }
}  
void MenuSystem::call       (void) {
    listMenu [selectCounter]->invokeCallback ( );  // call Callback 
}  
