#ifndef URL_ROLE
  #include<QAbstractItemView>
  #define URL_ROLE Qt::UserRole + 10
  #define TAG_ROLE URL_ROLE+1
#define DISABLE_ROLE URL_ROLE+2// a pseudo disable role to use instead of ~ItemIsEditable witch give us the abiliti to select the row
#endif