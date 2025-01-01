#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << QSqlDatabase :: drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signupbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_confirmbutton_clicked()
{
    // Check if the database connection already exists

        database = QSqlDatabase::addDatabase("QMYSQL");
        // Set connection parameters
        database.setHostName("localhost");  // Replace with your server's hostname or IP
        database.setDatabaseName("NMC");
        database.setUserName("root");
        database.setPassword("zainA42342");

        if (!database.open()) {
            QMessageBox::information(this, "Not connected", "Database not connected");
            return;
        }
        qDebug() << "ZAIN";


    // Retrieving data from input fields
    QString name = ui->nameSline->text();
    QString username = ui->usernameSline->text();
    QString password = ui->passwordSline->text();
    QString confirmpass = ui->confirmpasswordSline->text();
    QString hostel = ui->hostelSline->currentText();
    QString dept = ui->deptBox->currentText();
    QString contact = ui->contactSline->text();

    QRegularExpression regex("^03\\d{9}$");
    int check = 0;



    if (regex.match(contact).hasMatch()) {
        check = 1;
    }

    // Check password match and contact validation
    if (password == confirmpass && check == 1 ) {
        QSqlQuery qry;

        // Prepare the INSERT query
        qry.prepare("INSERT INTO hostelites (name, username, password, password2, hostel, department, contact) "
                    "VALUES (:name, :username, :password, :password2, :hostel, :department, :contact)");
        qry.bindValue(":name", name);
        qry.bindValue(":username", username);
        qry.bindValue(":password", password);
        qry.bindValue(":password2", confirmpass);
        qry.bindValue(":hostel", hostel);
        qry.bindValue(":department", dept);
        qry.bindValue(":contact", contact);

        if (qry.exec()) {
            QMessageBox::information(this, "Data inserted", "Data inserted successfully");
            ui->stackedWidget->setCurrentIndex(0);
        } else {
            QMessageBox::information(this, "Query Error", "Failed to insert data.");
        }
    }
    else if (password != confirmpass) {
        QMessageBox::information(this, "Incorrect password", "Please confirm your password again");
    }
    else if (check == 0) {
        QMessageBox::information(this, "Incorrect Contact", "Contact must be 11 digits and start with '03'");
    }


}


void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_signupbutton_2_clicked()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("NMC");
    database.setUserName("root");
    database.setPassword("zainA42342");

    QString username1 = ui->uline->text();
    QString password1 = ui->pline->text();

    if(database.open())
    {
        QSqlQuery query;
        query.prepare(QString("SELECT * FROM hostelites WHERE username = :username AND password = :password"));
        query.bindValue(":username", username1);
        query.bindValue(":password", password1);

        if(query.exec() && query.next()){
            QMessageBox::information(this,"Login Successful","SUCCESSFUL");

            // Fetch user details from the database
            QString name = query.value("name").toString();
            QString hostel = query.value("hostel").toString();
            QString contact = query.value("contact").toString();

            // Set these values in the respective UI fields

            ui->nameSline->setText(name);
            ui->hostelSline->setCurrentText(hostel);
            ui->contactSline->setText(contact);

            // Switch to the order page or another relevant UI page
            ui->stackedWidget->setCurrentIndex(2);
        }
        else{
            QMessageBox::information(this,"Login NOT Successful","FAILED");
        }
    }
    else{
        QMessageBox::information(this,"Database NOT connected","Database NOT connected");
    }
}





void MainWindow::on_nmcpharm_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);

}


void MainWindow::on_adminsignin_clicked()
{
    QString adminusername = ui->adminu->text();
    QString adminpass = ui->adminp->text();

    if (adminusername=="admin123" && adminpass == "admin123")
    {
        QMessageBox :: information (this,"Login Successful","Logged in to admin interface");
         ui->stackedWidget->setCurrentIndex(7);
    }
    else {
        QMessageBox :: information (this,"Login Unsuccessful","Invalid credentials for admin interface");
    }
}

    void MainWindow::on_confirmorder2_clicked()
    {
        database = QSqlDatabase::addDatabase("QMYSQL");
        database.setHostName("localhost");
        database.setDatabaseName("NMC");
        database.setUserName("root");
        database.setPassword("zainA42342");

        bool stockOk = true;
            if (database.open()) {

                // Prices of medicines (ideally fetched from the database)
                double priceAntibiotics = 0; // Azomax
                double pricePainkillers = 0;  // Paracetamol
                double priceAntivirals = 0;  // Histop
                double priceAntacids = 0;     // Flagyl
                double priceAntibiotics2 = 0; // augmentin DS
                double pricePainkillers2 = 0; // ibrufen
                double priceAntivirals2 = 0; // tamiflue
                double priceAntacids2 = 0;  // nexium

                QSqlQuery query;
                query.prepare("SELECT name, price FROM medicine");

                if (!query.exec()) {
                    qDebug() << "Failed to execute query:";
                    return;
                }

                while (query.next()) {
                    QString name = query.value("name").toString();  // Medicine name
                    double price = query.value("price").toDouble();  // Medicine price

                    // Check the medicine name and assign the price to the respective variable
                    if (name == "Azomax") priceAntibiotics = price;
                    else if (name == "Paracetamol") pricePainkillers = price;
                    else if (name == "Histop") priceAntivirals = price;
                    else if (name == "Flagyl") priceAntacids = price;
                    else if (name == "Augmentin DS") priceAntibiotics2 = price;
                    else if (name == "Ibrufen") pricePainkillers2 = price;
                    else if (name == "Tamiflue") priceAntivirals2 = price;
                    else if (name == "Nexium") priceAntacids2 = price;
                }

                // Retrieve quantities from line edits
                int qtyAntibiotics = ui->azomaxline->text().toInt();
                int qtyPainkillers = ui->paracetamolline->text().toInt();
                int qtyAntivirals = ui->histopline->text().toInt();
                int qtyAntacids = ui->flagylline->text().toInt();
                int qtyAntibiotics2 = ui->augmentinaline->text().toInt();
                int qtyPainkillers2 = ui->ibrufenaline->text().toInt();
                int qtyAntivirals2 = ui->tamialine->text().toInt();
                int qtyAntacids2 = ui->nexiumaline->text().toInt();



                // Check stock for each medicine and update if sufficient stock exists

                // Stock check and update for Azomax
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Azomax'");
                if (query.exec() && query.next()) {
                    int stockAntibiotics = query.value(0).toInt();
                    if (qtyAntibiotics > stockAntibiotics) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Azomax. Available: " + QString::number(stockAntibiotics));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Azomax'");
                        query.bindValue(":qty", qtyAntibiotics);
                        query.exec();
                    }
                }

                // Stock check and update for Paracetamol
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Paracetamol'");
                if (query.exec() && query.next()) {
                    int stockPainkillers = query.value(0).toInt();
                    if (qtyPainkillers > stockPainkillers) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Paracetamol. Available: " + QString::number(stockPainkillers));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Paracetamol'");
                        query.bindValue(":qty", qtyPainkillers);
                        query.exec();
                    }
                }

                // Stock check and update for Histop
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Histop'");
                if (query.exec() && query.next()) {
                    int stockAntivirals = query.value(0).toInt();
                    if (qtyAntivirals > stockAntivirals) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Histop. Available: " + QString::number(stockAntivirals));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Histop'");
                        query.bindValue(":qty", qtyAntivirals);
                        query.exec();
                    }
                }

                // Stock check and update for Flagyl
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Flagyl'");
                if (query.exec() && query.next()) {
                    int stockAntacids = query.value(0).toInt();
                    if (qtyAntacids > stockAntacids) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Flagyl. Available: " + QString::number(stockAntacids));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Flagyl'");
                        query.bindValue(":qty", qtyAntacids);
                        query.exec();
                    }
                }

                // Stock check and update for Augmentin
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Augmentin'");
                if (query.exec() && query.next()) {
                    int stockAntibiotics2 = query.value(0).toInt();
                    if (qtyAntibiotics2 > stockAntibiotics2) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Augmentin. Available: " + QString::number(stockAntibiotics2));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Augmentin'");
                        query.bindValue(":qty", qtyAntibiotics2);
                        query.exec();
                    }
                }

                // Stock check and update for Ibrufen
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Ibrufen'");
                if (query.exec() && query.next()) {
                    int stockPainkillers2 = query.value(0).toInt();
                    if (qtyPainkillers2 > stockPainkillers2) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Ibrufen. Available: " + QString::number(stockPainkillers2));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Ibrufen'");
                        query.bindValue(":qty", qtyPainkillers2);
                        query.exec();
                    }
                }

                // Stock check and update for Nexium
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Nexium'");
                if (query.exec() && query.next()) {
                    int stockAntacids2 = query.value(0).toInt();
                    if (qtyAntacids2 > stockAntacids2) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Nexium. Available: " + QString::number(stockAntacids2));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Nexium'");
                        query.bindValue(":qty", qtyAntacids2);
                        query.exec();
                    }
                }

                // Stock check and update for Tamiflu
                query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'Tamiflu'");
                if (query.exec() && query.next()) {
                    int stockAntivirals2 = query.value(0).toInt();
                    if (qtyAntivirals2 > stockAntivirals2) {
                        QMessageBox::warning(this, "Stock Error", "Not enough stock for Tamiflu. Available: " + QString::number(stockAntivirals2));
                        stockOk = false;
                    } else {
                        query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'Tamiflu'");
                        query.bindValue(":qty", qtyAntivirals2);
                        query.exec();
                    }
                }

                // If all stock checks passed, calculate total price
                if (stockOk) {
                    double totalPrice = (qtyAntibiotics * priceAntibiotics) +
                                        (qtyPainkillers * pricePainkillers) +
                                        (qtyAntivirals * priceAntivirals) +
                                        (qtyAntacids * priceAntacids) +
                                        (qtyAntibiotics2 * priceAntibiotics2) +
                                        (qtyPainkillers2 * pricePainkillers2) +
                                        (qtyAntivirals2 * priceAntivirals2) +
                                        (qtyAntacids2 * priceAntacids2);

                    QMessageBox::information(this, "Order Confirmed", "Your order has been confirmed! Total price: Rs " + QString::number(totalPrice));
                     ui->stackedWidget->setCurrentIndex(2);
                }
            } else {
                QMessageBox::information(this, "Error", "Database connection failed!");
            }

            // Get the logged-in user's username
            QString username = ui->usernameSline->text();  // Example, adjust based on your actual UI

            // Retrieve quantities from user input (QLineEdits)
            int qtyAzomax = ui->azomaxline->text().toInt();
            int qtyParacetamol = ui->paracetamolline->text().toInt();
            int qtyHistop = ui->histopline->text().toInt();
            int qtyFlagyl = ui->flagylline->text().toInt();
            int qtyAugmentin = ui->augmentinaline->text().toInt();
            int qtyIbrufen = ui->ibrufenaline->text().toInt();
            int qtyTamiflu = ui->tamialine->text().toInt();
            int qtyNexium = ui->nexiumaline->text().toInt();

            // Query to fetch hostelite details (name, hostel, and contact) from the hostelites table
            QSqlQuery query;
            QString hosteliteName, hostelName, contact;

            // Check if any of the fields are empty and fetch from database if they are
            if (ui->nameSline->text().isEmpty() || ui->hostelSline->currentText().isEmpty() || ui->contactSline->text().isEmpty()) {
                query.prepare("SELECT name, hostel, contact FROM hostelites WHERE username = :username");
                query.bindValue(":username", username);
                if (query.exec() && query.next()) {
                    hosteliteName = query.value(0).toString();
                    hostelName = query.value(1).toString();
                    contact = query.value(2).toString();
                } else {
                    QMessageBox::warning(this, "Error", "Failed to retrieve hostelite details.");
                    return; // Exit if hostelite details are not found
                }
            } else {
                // If the fields are not empty, use the values entered by the user
                hosteliteName = ui->nameSline->text();
                hostelName = ui->hostelSline->currentText();
                contact = ui->contactSline->text();
            }

            // Function to process each medicine if ordered (quantity > 0) and insert order into database
            auto placeOrder = [&](const QString& medicineName, int quantity) {
                if (quantity > 0) {
                    query.prepare("SELECT price FROM medicine WHERE name = :name");
                    query.bindValue(":name", medicineName);
                    if (query.exec() && query.next() && stockOk == true) {
                        double price = query.value(0).toDouble();
                        double totalPrice = price * quantity;

                        // Insert the order details into the orders table
                        query.prepare("INSERT INTO orders (username_order, hostelite_name, hostel_name, contact_order, medicine_name, quantity_order, price_order, total_price_order) "
                                      "VALUES (:username_order, :hostelite_name, :hostel_name, :contact_order, :medicine_name, :quantity_order, :price_order, :total_price_order)");
                        query.bindValue(":username_order", username);
                        query.bindValue(":hostelite_name", hosteliteName);
                        query.bindValue(":hostel_name", hostelName);
                        query.bindValue(":contact_order", contact);
                        query.bindValue(":medicine_name", medicineName);
                        query.bindValue(":quantity_order", quantity);
                        query.bindValue(":price_order", price);
                        query.bindValue(":total_price_order", totalPrice);
                        if (!query.exec()) {
                            QMessageBox::warning(this, "Order Error", "Failed to place order for " + medicineName);
                        }

                    }
                }
            };

            // Process the medicines and insert each order
            placeOrder("Azomax", qtyAzomax);
            placeOrder("Paracetamol", qtyParacetamol);
            placeOrder("Histop", qtyHistop);
            placeOrder("Flagyl", qtyFlagyl);
            placeOrder("Augmentin", qtyAugmentin);
            placeOrder("Ibrufen", qtyIbrufen);
            placeOrder("Tamiflu", qtyTamiflu);
            placeOrder("Nexium", qtyNexium);





            QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
            database.setHostName("localhost");
            database.setDatabaseName("NMC");
            database.setUserName("root");
            database.setPassword("zainA42342");

            if (database.open()) {
                QSqlQuery query;
                QString hosteliteName, hostelName, contact;

                if (ui->nameSline->text().isEmpty() || ui->hostelSline->currentText().isEmpty() || ui->contactSline->text().isEmpty()) {
                    query.prepare("SELECT name, hostel, contact FROM hostelites WHERE username = :username");
                    query.bindValue(":username", username);
                    if (query.exec() && query.next()) {
                        hosteliteName = query.value(0).toString();
                        hostelName = query.value(1).toString();
                        contact = query.value(2).toString();
                    } else {
                        QMessageBox::warning(this, "Error", "Failed to retrieve hostelite details.");
                        return; // Exit if hostelite details are not found
                    }
                } else {
                    hosteliteName = ui->nameSline->text();
                    hostelName = ui->hostelSline->currentText();
                    contact = ui->contactSline->text();
                }

                // Check if username is valid
                qDebug() << "Username: " << username;

                // Query to fetch order data
                query.prepare("SELECT hostelite_name, hostel_name, contact_order, medicine_name, quantity_order, total_price_order, order_date "
                              "FROM orders WHERE username_order = :username ORDER BY hostelite_name, order_date");
                query.bindValue(":username", username);

                if (query.exec()) {
                    qDebug() << "Executed query: " << query.lastQuery();  // Check the actual quer

                    // Loop through each row in the result
                    while (query.next()) {
                        int rowCount = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(rowCount);  // Add a new row

                        // Insert data into table columns
                        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(query.value("hostelite_name").toString()));
                        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(query.value("hostel_name").toString()));
                        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(query.value("contact_order").toString()));
                        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(query.value("medicine_name").toString()));
                        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(query.value("quantity_order").toString()));
                        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(query.value("total_price_order").toString()));
                        ui->tableWidget->setItem(rowCount, 6, new QTableWidgetItem(query.value("order_date").toString()));
                    }
                } else {
                    QMessageBox::warning(this, "Query Execution Failed", "Failed");
                }
            } else {
                QMessageBox::warning(this, "Database Error", "Failed to connect to the database");
            }
    }



        void MainWindow::on_typemed_clicked()
        {
             ui->stackedWidget->setCurrentIndex(4);
        }


        void MainWindow::on_diseaseconfirm_clicked()
        {
            database = QSqlDatabase::addDatabase("QMYSQL");
            database.setHostName("localhost");
            database.setDatabaseName("NMC");
            database.setUserName("root");
            database.setPassword("zainA42342");

                bool stockOk = true;
                if (database.open()) {
                    // Prices of medicines (ideally fetched from the database)
                    double pricePanadolExtra = 0;
                    double priceArinac = 0;
                    double priceImodium = 0;
                    double priceORS = 0;
                    double priceRondec = 0;
                    double priceHydrillin = 0;
                    double priceAlp = 0;
                    double priceXanax = 0;
                    double priceAmodip = 0;
                    double priceSofvasc = 0;


                    QSqlQuery query;
                    query.prepare("SELECT name, price FROM medicine");

                    if (!query.exec()) {
                        qDebug() << "Failed to execute query:";
                        return;
                    }

                    // Store prices in variables
                    while (query.next()) {
                        QString name = query.value("name").toString();
                        double price = query.value("price").toDouble();

                        if (name == "panadolextra") pricePanadolExtra = price;
                        else if (name == "arinac") priceArinac = price;
                        else if (name == "imodium") priceImodium = price;
                        else if (name == "ORS") priceORS = price;
                        else if (name == "rondec") priceRondec = price;
                        else if (name == "hydrillin") priceHydrillin = price;
                        else if (name == "alp") priceAlp = price;
                        else if (name == "xanax") priceXanax = price;
                        else if (name == "amodip") priceAmodip = price;
                        else if (name == "sofvasc") priceSofvasc = price;
                    }

                    // Retrieve quantities from line edits
                    int qtyPanadolExtra = ui->panadolline->text().toInt();
                    int qtyArinac = ui->arinacline->text().toInt();
                    int qtyImodium = ui->imodiumline->text().toInt();
                    int qtyORS = ui->orsline->text().toInt();
                    int qtyRondec = ui->rondecline->text().toInt();
                    int qtyHydrillin = ui->hydrillinline->text().toInt();
                    int qtyAlp = ui->alpline->text().toInt();
                    int qtyXanax = ui->xanaxline->text().toInt();
                    int qtyAmodip = ui->amodipline->text().toInt();
                    int qtySofvasc = ui->sofvascline->text().toInt();



                    // Check stock for each medicine and update if sufficient stock exists

                    // Stock check and update for Panadol Extra
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'panadolextra'");
                    if (query.exec() && query.next()) {
                        int stockPanadolExtra = query.value(0).toInt();
                        if (qtyPanadolExtra > stockPanadolExtra) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Panadol Extra. Available: " + QString::number(stockPanadolExtra));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'panadolextra'");
                            query.bindValue(":qty", qtyPanadolExtra);
                            query.exec();
                        }
                    }

                    // Stock check and update for Arinac
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'arinac'");
                    if (query.exec() && query.next()) {
                        int stockArinac = query.value(0).toInt();
                        if (qtyArinac > stockArinac) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Arinac. Available: " + QString::number(stockArinac));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'arinac'");
                            query.bindValue(":qty", qtyArinac);
                            query.exec();
                        }
                    }

                    // Stock check and update for Imodium
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'imodium'");
                    if (query.exec() && query.next()) {
                        int stockImodium = query.value(0).toInt();
                        if (qtyImodium > stockImodium) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Imodium. Available: " + QString::number(stockImodium));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'imodium'");
                            query.bindValue(":qty", qtyImodium);
                            query.exec();
                        }
                    }

                    // Stock check and update for ORS
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'ORS'");
                    if (query.exec() && query.next()) {
                        int stockORS = query.value(0).toInt();
                        if (qtyORS > stockORS) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for ORS. Available: " + QString::number(stockORS));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'ORS'");
                            query.bindValue(":qty", qtyORS);
                            query.exec();
                        }
                    }

                    // Stock check and update for Rondec
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'rondec'");
                    if (query.exec() && query.next()) {
                        int stockRondec = query.value(0).toInt();
                        if (qtyRondec > stockRondec) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Rondec. Available: " + QString::number(stockRondec));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'rondec'");
                            query.bindValue(":qty", qtyRondec);
                            query.exec();
                        }
                    }

                    // Stock check and update for Hydrillin
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'hydrillin'");
                    if (query.exec() && query.next()) {
                        int stockHydrillin = query.value(0).toInt();
                        if (qtyHydrillin > stockHydrillin) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Hydrillin. Available: " + QString::number(stockHydrillin));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'hydrillin'");
                            query.bindValue(":qty", qtyHydrillin);
                            query.exec();
                        }
                    }

                    // Stock check and update for Alp
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'alp'");
                    if (query.exec() && query.next()) {
                        int stockAlp = query.value(0).toInt();
                        if (qtyAlp > stockAlp) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Alp. Available: " + QString::number(stockAlp));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'alp'");
                            query.bindValue(":qty", qtyAlp);
                            query.exec();
                        }
                    }

                    // Stock check and update for Xanax
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'xanax'");
                    if (query.exec() && query.next()) {
                        int stockXanax = query.value(0).toInt();
                        if (qtyXanax > stockXanax) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Xanax. Available: " + QString::number(stockXanax));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'xanax'");
                            query.bindValue(":qty", qtyXanax);
                            query.exec();
                        }
                    }

                    // Stock check and update for Amodip
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'amodip'");
                    if (query.exec() && query.next()) {
                        int stockAmodip = query.value(0).toInt();
                        if (qtyAmodip > stockAmodip) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Xanax. Available: " + QString::number(stockAmodip));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'amodip'");
                            query.bindValue(":qty", qtyAmodip);
                            query.exec();
                        }
                    }
                    // Stock check and update for Amodip
                    query.prepare("SELECT stock_quantity FROM medicine WHERE name = 'sofvasc'");
                    if (query.exec() && query.next()) {
                        int stockSofvasc = query.value(0).toInt();
                        if (qtySofvasc > stockSofvasc) {
                            QMessageBox::warning(this, "Stock Error", "Not enough stock for Xanax. Available: " + QString::number(stockSofvasc));
                            stockOk = false;
                        } else {
                            query.prepare("UPDATE medicine SET stock_quantity = stock_quantity - :qty WHERE name = 'sofvasc'");
                            query.bindValue(":qty", qtySofvasc);
                            query.exec();
                        }
                    }


                    // If all stock checks passed, calculate total price
                    if (stockOk) {
                        double totalPrice = (qtyPanadolExtra * pricePanadolExtra) +
                                            (qtyArinac * priceArinac) +
                                            (qtyImodium * priceImodium) +
                                            (qtyORS * priceORS) +
                                            (qtyRondec * priceRondec) +
                                            (qtyHydrillin * priceHydrillin) +
                                            (qtyAlp * priceAlp) +
                                            (qtyXanax * priceXanax) +
                                            (qtyAmodip * priceAmodip) +
                                            (qtySofvasc * priceSofvasc);

                        QMessageBox::information(this, "Order Confirmed", "Your order has been confirmed! Total price: Rs " + QString::number(totalPrice));
                         ui->stackedWidget->setCurrentIndex(2);
                    }
                } else {
                    QMessageBox::information(this, "Error", "Database connection failed!");
                }
                // Get the logged-in user's username
                QString username = ui->usernameSline->text();  // Example, adjust based on your actual UI

                // Retrieve quantities from user input (QLineEdits)
                int qtyPanadolExtra = ui->panadolline->text().toInt();
                int qtyArinac = ui->arinacline->text().toInt();
                int qtyImodium = ui->imodiumline->text().toInt();
                int qtyORS = ui->orsline->text().toInt();
                int qtyRondec = ui->rondecline->text().toInt();
                int qtyHydrillin = ui->hydrillinline->text().toInt();
                int qtyAlp = ui->alpline->text().toInt();
                int qtyXanax = ui->xanaxline->text().toInt();
                int qtyAmodip = ui->amodipline->text().toInt();
                int qtySofvasc = ui->sofvascline->text().toInt();

                // Query to fetch hostelite details (name, hostel, and contact) from the hostelites table
                QSqlQuery query;
                QString hosteliteName, hostelName, contact;

                // Check if any of the fields are empty and fetch from database if they are
                if (ui->nameSline->text().isEmpty() || ui->hostelSline->currentText().isEmpty() || ui->contactSline->text().isEmpty()) {
                    query.prepare("SELECT name, hostel, contact FROM hostelites WHERE username = :username");
                    query.bindValue(":username", username);
                    if (query.exec() && query.next()) {
                        hosteliteName = query.value(0).toString();
                        hostelName = query.value(1).toString();
                        contact = query.value(2).toString();
                    } else {
                        QMessageBox::warning(this, "Error", "Failed to retrieve hostelite details.");
                        return; // Exit if hostelite details are not found
                    }
                } else {
                    // If the fields are not empty, use the values entered by the user
                    hosteliteName = ui->nameSline->text();
                    hostelName = ui->hostelSline->currentText();
                    contact = ui->contactSline->text();
                }

                // Function to process each medicine if ordered (quantity > 0) and insert order into database
                auto placeOrder = [&](const QString& medicineName, int quantity) {
                    if (quantity > 0) {
                        query.prepare("SELECT price FROM medicine WHERE name = :name");
                        query.bindValue(":name", medicineName);
                        if (query.exec() && query.next() && stockOk == true) {
                            double price = query.value(0).toDouble();
                            double totalPrice = price * quantity;

                            // Insert the order details into the orders table
                            query.prepare("INSERT INTO orders (username_order, hostelite_name, hostel_name, contact_order, medicine_name, quantity_order, price_order, total_price_order) "
                                          "VALUES (:username_order, :hostelite_name, :hostel_name, :contact_order, :medicine_name, :quantity_order, :price_order, :total_price_order)");
                            query.bindValue(":username_order", username);
                            query.bindValue(":hostelite_name", hosteliteName);
                            query.bindValue(":hostel_name", hostelName);
                            query.bindValue(":contact_order", contact);
                            query.bindValue(":medicine_name", medicineName);
                            query.bindValue(":quantity_order", quantity);
                            query.bindValue(":price_order", price);
                            query.bindValue(":total_price_order", totalPrice);
                            if (!query.exec()) {
                                QMessageBox::warning(this, "Order Error", "Failed to place order for " + medicineName);
                            }
                        }
                    }
                };

                // Process the medicines and insert each order
                placeOrder("PanadolExtra",qtyPanadolExtra);
                placeOrder("Arinac",qtyArinac);
                placeOrder("Imodium",qtyImodium);
                placeOrder("ORS",qtyORS);
                placeOrder("Rondec",qtyRondec);
                placeOrder("Hydrillin",qtyHydrillin);
                placeOrder("Alp",qtyAlp );
                placeOrder("Xanax",qtyXanax);
                placeOrder("Amodip",qtyAmodip);
                placeOrder("Sofvasc",qtySofvasc);

                QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
                database.setHostName("localhost");
                database.setDatabaseName("NMC");
                database.setUserName("root");
                database.setPassword("zainA42342");

                if (database.open()) {
                    QSqlQuery query;
                    QString hosteliteName, hostelName, contact;

                    if (ui->nameSline->text().isEmpty() || ui->hostelSline->currentText().isEmpty() || ui->contactSline->text().isEmpty()) {
                        query.prepare("SELECT name, hostel, contact FROM hostelites WHERE username = :username");
                        query.bindValue(":username", username);
                        if (query.exec() && query.next()) {
                            hosteliteName = query.value(0).toString();
                            hostelName = query.value(1).toString();
                            contact = query.value(2).toString();
                        } else {
                            QMessageBox::warning(this, "Error", "Failed to retrieve hostelite details.");
                            return; // Exit if hostelite details are not found
                        }
                    } else {
                        hosteliteName = ui->nameSline->text();
                        hostelName = ui->hostelSline->currentText();
                        contact = ui->contactSline->text();
                    }

                    // Check if username is valid
                    qDebug() << "Username: " << username;

                    // Query to fetch order data
                    query.prepare("SELECT hostelite_name, hostel_name, contact_order, medicine_name, quantity_order,price_order, total_price_order, order_date "
                                  "FROM orders WHERE username_order = :username ORDER BY hostelite_name, order_date");
                    query.bindValue(":username", username);

                    if (query.exec()) {
                        qDebug() << "Executed query: " << query.lastQuery();  // Check the actual query


                        // Loop through each row in the result
                        while (query.next()) {
                            int rowCount = ui->tableWidget->rowCount();
                            ui->tableWidget->insertRow(rowCount);  // Add a new row

                            // Insert data into table columns
                            ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(query.value("hostelite_name").toString()));
                            ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(query.value("hostel_name").toString()));
                            ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(query.value("contact_order").toString()));
                            ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(query.value("medicine_name").toString()));
                            ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(query.value("quantity_order").toString()));
                            ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(query.value("price_order").toString()));
                            ui->tableWidget->setItem(rowCount, 6, new QTableWidgetItem(query.value("total_price_order").toString()));
                            ui->tableWidget->setItem(rowCount, 7, new QTableWidgetItem(query.value("order_date").toString()));

                        }
                    } else {
                        QMessageBox::warning(this, "Query Execution Failed", "Failed");
                    }
                } else {
                    QMessageBox::warning(this, "Database Error", "Failed to connect to the database");
                }
        }
        void MainWindow::on_vieworderbutton_clicked()
        {
            ui->stackedWidget->setCurrentIndex(11);
            // Establish a connection to the MySQL database
            QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
            database.setHostName("localhost");
            database.setDatabaseName("NMC");
            database.setUserName("root");
            database.setPassword("zainA42342");

            if (database.open())
            {
                QSqlQuery query("SELECT * FROM orders");

                if (!query.exec()) {
                    qDebug() << "Query execution failed:" ;
                    return;
                }

                // Clear existing rows in the table widget
                ui->tableWidget->setRowCount(0);
                ui->tableWidget->setColumnCount(10); // Set columns
                ui->tableWidget->setHorizontalHeaderLabels({
                    "order_id", "username_order", "hostelite_name", "hostel_name",
                    "contact_order", "medicine_name", "quantity_order",
                    "price_order", "total_price_order", "order_date"
                });

                // Populate table with data
                int row = 0;
                while (query.next()) {
                    ui->tableWidget->insertRow(row);
                    for (int col = 0; col < 11; ++col) { // Adjust column count as per your table
                        QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                        ui->tableWidget->setItem(row, col, item);
                    }
                    ++row;
                }
            }




        }



                void MainWindow::on_pushButton_8_clicked()
                {
                     ui->stackedWidget->setCurrentIndex(2);
                }


                void MainWindow::on_adminsignin_2_clicked()
                {
                     ui->stackedWidget->setCurrentIndex(0);
                }


                void MainWindow::on_vieworderbutton_2_clicked()
                {
                     ui->stackedWidget->setCurrentIndex(6);
                }


                void MainWindow::on_vieworderbutton_3_clicked()
                {

                }


                void MainWindow::on_pushButton_10_clicked()
                {
                     ui->stackedWidget->setCurrentIndex(8);
                }


                void MainWindow::on_pushButton_11_clicked()
                {

                    // Establish database connection
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");
                    database.setDatabaseName("NMC");
                    database.setUserName("root");
                    database.setPassword("zainA42342");

                    if (database.open()) {
                        // Get the medicine name, new stock, and price from QLineEdits
                        QString medicineName = ui->medicineComboBox->currentText();
                        int newStock = ui->newstock->text().toInt();

                        if (medicineName.isEmpty() || newStock <= 0 ) {
                            QMessageBox::warning(this, "Input Error", "Please enter valid medicine details.");
                            return;
                        }

                        // Create a QSqlQuery object
                        QSqlQuery query;

                        // Prepare the query to update the stock quantity and price
                        query.prepare("UPDATE medicine SET stock_quantity = :stock  WHERE name = :name");
                        query.bindValue(":stock", newStock);
                        query.bindValue(":name", medicineName);

                        // Execute the query
                        if (query.exec()) {
                            QMessageBox::information(this, "Success", "Medicine stock updated successfully.");
                        } else {
                            QMessageBox::warning(this, "Error", "Failed to update medicine details. Please try again.");
                        }
                    } else {
                        QMessageBox::warning(this, "Database Error", "Failed to connect to the database.");
                    }
                }


                void MainWindow::on_pushButton_12_clicked()
                {
                    // Establish database connection
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");
                    database.setDatabaseName("NMC");
                    database.setUserName("root");
                    database.setPassword("zainA42342");

                    if (database.open()) {
                        // Get the medicine name, new stock, and price from QLineEdits
                        QString medicineName = ui->medicineComboBox->currentText();
                        double newPrice = ui->newprice->text().toDouble();

                        if (medicineName.isEmpty() || newPrice <= 0) {
                            QMessageBox::warning(this, "Input Error", "Please enter valid medicine details.");
                            return;
                        }

                        // Create a QSqlQuery object
                        QSqlQuery query;

                        // Prepare the query to update the stock quantity and price
                        query.prepare("UPDATE medicine SET price = :price WHERE name = :name");
                        query.bindValue(":price", newPrice);
                        query.bindValue(":name", medicineName);

                        // Execute the query
                        if (query.exec()) {
                            QMessageBox::information(this, "Success", "Medicine price updated successfully.");
                        } else {
                            QMessageBox::warning(this, "Error", "Failed to update medicine details. Please try again.");
                        }
                    } else {
                        QMessageBox::warning(this, "Database Error", "Failed to connect to the database.");
                    }
                }

                void MainWindow::on_pushButton_13_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 1");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->azomaxP->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }



                void MainWindow::on_pushButton_14_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 2");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->paracetamolp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_15_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 3");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->histopp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_16_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 4");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->flagylp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_17_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 5");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->augmentinp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_18_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 6");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->ibrufenp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_19_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 8");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->tamiflup->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_20_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 7");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->nexiump->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_21_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 9");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->panadolextrap->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_30_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 10");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->arinacp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_22_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 11");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->imodiump->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_29_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 12");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->orsp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_23_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 13");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->rondecp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_28_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 14");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->hydrillinp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_24_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 17");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->amodipp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_27_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 18");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->sofvascp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_25_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 15");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->alpp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_26_clicked()
                {
                    database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password
                    // Ensure the database connection is open
                    QSqlDatabase db = QSqlDatabase::database(); // Use existing connection or create new
                    if (!db.isOpen()) {
                        qDebug() << "Database not open!";
                        return;
                    }

                    QSqlQuery query;
                    query.prepare("SELECT price FROM medicine WHERE id = 16");

                    if (!query.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    if (query.next()) {
                        double price = query.value(0).toDouble();
                        qDebug() << "Price retrieved: " << price;  // Log the value
                        ui->xanaxp->setText(QString::number(price, 'f', 2));
                    } else {
                        qDebug() << "No matching record found.";
                    }
                }


                void MainWindow::on_pushButton_31_clicked()
                {
                    ui->stackedWidget->setCurrentIndex(2);
                }


                void MainWindow::on_pushButton_32_clicked()
                {
                    ui->stackedWidget->setCurrentIndex(2);
                }


                void MainWindow::on_pushButton_34_clicked()
                {
                     ui->stackedWidget->setCurrentIndex(10);

                }


                void MainWindow::on_pushButton_35_clicked()
                {
                    // Set up the database connection
                    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
                    database.setHostName("localhost");  // or the correct server IP
                    database.setDatabaseName("NMC");
                    database.setUserName("root");      // your MySQL username
                    database.setPassword("zainA42342"); // your MySQL password

                    // Attempt to open the database connection
                    if (!database.open()) {
                        qDebug() << "Database connection failed: " ;
                        return;
                    }

                    // Retrieve input data from the UI
                    QString address = ui->addressline->text();
                    QString hostelite_name = ui->nameSline->text();
                    QString hostel_name = ui->hostelSline->currentText();
                    QString contact_number = ui->contactSline->text();

                    // Prepare the SQL query
                    QSqlQuery qry;
                    qry.prepare("INSERT INTO calls (address, hostel, hostelite_name, contact_number) "
                                "VALUES (:address, :hostel, :hostelite_name, :contact_number)");
                    qry.bindValue(":address", address);
                    qry.bindValue(":hostel", hostel_name);
                    qry.bindValue(":hostelite_name", hostelite_name);
                    qry.bindValue(":contact_number", contact_number);

                    // Execute the query and check for errors
                    if (!qry.exec()) {
                        qDebug() << "Query failed: ";
                        return;
                    }

                    // Show success message
                    QMessageBox::information(this, "Call forwarded successfully",
                                             "Please wait for the call at your number, we are arriving!!");

                    // Close the database connection
                    database.close();
                }



                void MainWindow::on_pushButton_3_clicked()
                {
                    ui->stackedWidget->setCurrentIndex(10);
                }


                void MainWindow::on_pushButton_36_clicked()
                {
                        // Set up the database connection
                        QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
                        database.setHostName("localhost");
                        database.setDatabaseName("NMC");
                        database.setUserName("root");
                        database.setPassword("zainA42342");

                        // Attempt to open the database
                        if (!database.open()) {
                            QMessageBox::critical(this, "Error", "Failed to connect to the database: " );
                            return;
                        }

                        // Prepare the SQL query
                        QSqlQuery qry;
                        qry.prepare("SELECT id, address, hostel, hostelite_name, contact_number FROM calls");

                        // Execute the query and check for errors
                        if (!qry.exec()) {
                            QMessageBox::critical(this, "Error", "Failed to retrieve data: ");
                            return;
                        }

                        // Build a string to display in the message box
                        QString result = "Call Records:\n\n";
                        while (qry.next()) {
                            int id = qry.value("id").toInt();
                            QString address = qry.value("address").toString();
                            QString hostel = qry.value("hostel").toString();
                            QString hostelite_name = qry.value("hostelite_name").toString();
                            QString contact_number = qry.value("contact_number").toString();

                            result += QString("ID: %1\nAddress: %2\nHostel: %3\nHostelite Name: %4\nContact Number: %5\n\n")
                                          .arg(id)
                                          .arg(address)
                                          .arg(hostel)
                                          .arg(hostelite_name)
                                          .arg(contact_number);
                        }

                        // Display the result in a message box
                        QMessageBox::information(this, "Call Records", result);

                        // Close the database connection
                        database.close();
                    }



                    void MainWindow::on_pushButton_33_clicked()
                    {
                        ui->stackedWidget->setCurrentIndex(2);
                    }


                    void MainWindow::on_pushButton_37_clicked()
                    {
                         ui->stackedWidget->setCurrentIndex(2);
                    }


                    void MainWindow::on_prev_clicked()
                    {
                          ui->stackedWidget->setCurrentIndex(7);
                    }


                    void MainWindow::on_prev_2_clicked()
                    {
                        ui->stackedWidget->setCurrentIndex(7);
                    }


