#include "dal/idal.hpp"
void insert_query(connection & C){
 /* Create SQL statement */
      std::string sql = "CREATE TABLE user_passwords("  \
                        "user_id INT REFERENCES users(id)," \
                        "encrypted_password varchar(256)   NOT NULL" \
                        ");";

      /* Create a transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Table created successfully" << endl;
};
void select_query(connection &C){
/* Create SQL statement */
      string sql = "SELECT u.id,u.first_name,u.last_name,u.email,u.phone,p.encrypted_password from users u join user_passwords p on (u.id=p.user_id)";

      /* Create a non-transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "ID = " << c[0].as<int>() << endl;
         cout << "Name = " << c[1].as<string>() << endl;
         cout << "Last Name = " << c[2].as<string>() << endl;
         cout << "email = " << c[3].as<string>() << endl;
         cout << "Phone = " << c[4].as<string>() << endl;
         cout << "Password = " << c[5].as<string>() << endl;
      }
      cout << "Operation done successfully" << endl;
};

int checkdb()
 {
   try {
      connection C("dbname = analyticsDB user = fran password = admin \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

        select_query(C);
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }

}