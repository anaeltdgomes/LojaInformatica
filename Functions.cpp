#include "Functions.h"

void hideWindow(HWND hwnd) {
    if (IsWindowVisible(hwnd))
        ShowWindow(hwnd, 0);
    else
        ShowWindow(hwnd, 1);
    UpdateWindow(hwnd);
}

void centralize(HWND window) {
    RECT rcClient = { 0 };
    GetWindowRect(window, &rcClient); //get window rect of control relative to screen
    int windowWidth = rcClient.right - rcClient.left;
    int windowHeight = rcClient.bottom - rcClient.top;
    MoveWindow(window, (mainWindowRec.right / 2) - (windowWidth / 2),
        (mainWindowRec.bottom / 2) - (windowHeight / 2), windowWidth, windowHeight, true);
}

void translate(HWND window, int moveX, int moveY, int widthPlus = 0, int heightPlus = 0) {
    RECT rcClient = { 0 };
    GetWindowRect(window, &rcClient); //get window rect of control relative to screen
    MapWindowPoints(NULL, GetParent(window), (LPPOINT)&rcClient, 2);
    rcClient.left += moveX;
    rcClient.top += moveY;
    //rcClient.right += widthPlus; // Aumenta tamanho
    //rcClient.bottom += heightPlus;
    SetWindowPos(window, HWND_TOP, rcClient.left, rcClient.top, returnWidth(window) + widthPlus, 
        returnHeight(window) + heightPlus, 0);
}

int returnWidth(HWND window) {
    RECT rcClient = { 0 };
    GetWindowRect(window, &rcClient); //get window rect of control relative to screen
    int windowWidth = rcClient.right - rcClient.left;
    return windowWidth;
}

int returnHeight(HWND window) {
    RECT rcClient = { 0 };
    GetWindowRect(window, &rcClient); //get window rect of control relative to screen
    int windowHeight = rcClient.bottom - rcClient.top;
    return windowHeight;
}

int returnPosX(HWND window) {
    RECT rcClient = { 0 };
    GetWindowRect(window, &rcClient); //get window rect of control relative to screen
    MapWindowPoints(NULL, GetParent(window), (LPPOINT)&rcClient, 2);
    return rcClient.left;
}

int returnPosY(HWND window) {
    RECT rcClient = { 0 };
    GetWindowRect(window, &rcClient); //get window rect of control relative to screen
    MapWindowPoints(NULL, GetParent(window), (LPPOINT)&rcClient, 2);
    return rcClient.top;
}

void showEmployee(ListView& lisViewObj, int numActive = 1) {
    //------ Database - Employee ------------//
    int rc;
    int error = 0, i = 0;
    sqlite3* db;
    sqlite3_stmt* stmt = nullptr;
    int age;
    double salary;
    const unsigned char* name, * sex, * job, * admission;
    stringstream resultadoSQL;

    sqlite3_open("SQL\\LojaTI.db", &db); // Se o Bando de Dados não existir ele é criado

    if (numActive == 1) {
        // Faz uma consulta na Tabela e envia para stmt
        rc = sqlite3_prepare_v2(db, "select Nome, Sexo, Idade, Cargo, Salario, Admissao from Employee where Ativo=\"1\";", -1, &stmt, 0);
    }
    else {
        rc = sqlite3_prepare_v2(db, "select Nome, Sexo, Idade, Cargo, Salario, Admissao from Employee where Ativo=\"0\";", -1, &stmt, 0);
    }
    error = sqlite3_step(stmt);
    do {
        name = sqlite3_column_text(stmt, 0);
        sex = sqlite3_column_text(stmt, 1);
        age = sqlite3_column_int(stmt, 2);
        job = sqlite3_column_text(stmt, 3);
        salary = sqlite3_column_double(stmt, 4);
        admission = sqlite3_column_text(stmt, 5);

        lisViewObj.SetRow((const char*)name, i, 0);
        lisViewObj.SetRow((const char*)sex, i, 1);
        resultadoSQL.str("");
        resultadoSQL << age;
        lisViewObj.SetRow(resultadoSQL.str().c_str(), i, 2);
        lisViewObj.SetRow((const char*)job, i, 3);
        resultadoSQL.str("");
        resultadoSQL << "R$ " << salary << ",00";
        lisViewObj.SetRow(resultadoSQL.str().c_str(), i, 4);
        lisViewObj.SetRow((const char*)admission, i, 5);

        i++;
        resultadoSQL.str("");
        error = sqlite3_step(stmt);
    } while (error != SQLITE_DONE);

    sqlite3_close(db);
}

char addEmployeeFunction(HWND hwnd, string textEmployeeEdit, string textEmployeeSexEdit, string textEmployeeAgeEdit,
    string textEmployeeJobEdit, string textEmployeeSalaryEdit, string textEmployeeAdmissionEdit) {
    int rc;
    int error = 0;
    char* messageError = (char*)"";
    string queryImput;

    // Previne Sql injection caso coloquem uma virgula no campo salário
    size_t found = textEmployeeSalaryEdit.find(",");
    if (found != string::npos) {
        textEmployeeSalaryEdit.replace(found, found, ".");
    }

    if ((textEmployeeEdit != "") && (textEmployeeSexEdit != "") && (textEmployeeAgeEdit != "")
        && (textEmployeeJobEdit != "") && (textEmployeeSalaryEdit != "") && (textEmployeeAdmissionEdit != "")) 
    {
        queryImput = "insert into Employee (Nome, Sexo, Idade, Ativo, Cargo, Salario, Admissao) values ('" +
            textEmployeeEdit + "', '" + textEmployeeSexEdit + "', " + textEmployeeAgeEdit + ", 1, '" +
            textEmployeeJobEdit + "', " + textEmployeeSalaryEdit + ", '" + textEmployeeAdmissionEdit + "');";

        sqlite3* db;
        sqlite3_open("SQL\\LojaTI.db", &db);
        rc = sqlite3_exec(db, queryImput.c_str(), NULL, 0, &messageError);
        sqlite3_close(db);
        
        if (messageError != SQLITE_OK) {
            MessageBox(hwnd, "Deu erro no Banco de Dados. \nInsira apenas números nos campos Idade e Salário.",
                "Mensagem de erro!", MB_ICONEXCLAMATION | MB_OK);
        }
        else {
            return (char)messageError;
        }
    }else {
        MessageBox(hwnd, "Preencha todos os dados corretamente.", "Mensagem de erro!",
            MB_ICONEXCLAMATION | MB_OK);
    }
}

int showVendas(int num, Label& labelObj1, Label& labelObj2, Label& labelObj3, Label& labelObj4, Label& labelObj5, Label& labelObj6, Label& labelObj7) {
    //------ Database - Vendas ------------//
    int rc, rc2;
    int error = 0, maxID = 0, i = 0;
    sqlite3* db;
    sqlite3_stmt* stmt, *stmt2;
    int quantity, product;
    double value, price;
    const unsigned char* date, * vendor, * name, * url;
    stringstream resultadoSQL;

    sqlite3_open("SQL\\LojaTI.db", &db); // Abre o Bando de Dados
    
    rc2 = sqlite3_prepare_v2(db, "select count(ID) from Vendas;", -1, &stmt2, 0);
    error = sqlite3_step(stmt2);
    maxID = sqlite3_column_int(stmt2, 0);

    if (num <= maxID) {
        resultadoSQL.str("");
        resultadoSQL << "Vendas: " << num << "/" << maxID;
        labelObj1.SetText(resultadoSQL.str().c_str());

        resultadoSQL.str("");
        resultadoSQL << "select V.Produto, V.Quantidade, V.Valor, V.Data, V.Vendedor, P.Name, P.Price, P.Url from Vendas V inner join Product P on V.Produto = P.ID where V.ID='" << num << "';";
        // Faz uma consulta na Tabela e envia para stmt
        rc = sqlite3_prepare_v2(db, resultadoSQL.str().c_str(), -1, &stmt, 0);

        error = sqlite3_step(stmt);

        product = sqlite3_column_int(stmt, 0);
        quantity = sqlite3_column_int(stmt, 1);
        value = sqlite3_column_double(stmt, 2);
        date = sqlite3_column_text(stmt, 3);
        vendor = sqlite3_column_text(stmt, 4);
        name = sqlite3_column_text(stmt, 5);
        price = sqlite3_column_double(stmt, 6);
        url = sqlite3_column_text(stmt, 7);

        resultadoSQL.str("");
        resultadoSQL << "Produto:\n \t" << name;
        labelObj2.SetText(resultadoSQL.str().c_str());
        resultadoSQL.str("");
        resultadoSQL << "Quantidade:\n \t" << to_string(quantity);
        labelObj3.SetText(resultadoSQL.str().c_str());
        resultadoSQL.str("");
        resultadoSQL << "Vendedor:\n \t" << vendor;
        labelObj4.SetText(resultadoSQL.str().c_str());
        resultadoSQL.str("");
        resultadoSQL << "Data:\n \t" << date;
        labelObj5.SetText(resultadoSQL.str().c_str());
        resultadoSQL.str("");
        resultadoSQL << "Preço:\n \tR$" << to_string((int)price) << ",00";
        labelObj6.SetText(resultadoSQL.str().c_str());
        resultadoSQL.str("");
        resultadoSQL << "Total:\n \tR$" << to_string(((int)price) * quantity) << ",00";
        labelObj7.SetText(resultadoSQL.str().c_str());
    }
    else { contadorVendas = maxID; }

    sqlite3_close(db);
    return maxID;
}

void showVendas(ListView& listViewObj) {
    //--------- Database - Vendas ---------//
    int rc;
    int error = 0, i = 0;
    sqlite3* db;
    sqlite3_stmt* stmt;
    int quantity, product;
    double value, price;
    const unsigned char* date, * vendor, * name, * url;
    string resultadoSQL;
    resultadoSQL = "";
    sqlite3_open("SQL\\LojaTI.db", &db); // Abre o Bando de Dados
    
    // Faz uma consulta na Tabela e envia para stmt
    rc = sqlite3_prepare_v2(db,
        "select V.Produto, V.Quantidade, V.Valor, V.Data, V.Vendedor, P.Name, P.Price, P.Url from Vendas V inner join Product P on V.Produto = P.ID;",
        -1, &stmt, 0);

    error = sqlite3_step(stmt);
    do {
        product = sqlite3_column_int(stmt, 0);
        quantity = sqlite3_column_int(stmt, 1);
        value = sqlite3_column_double(stmt, 2);
        date = sqlite3_column_text(stmt, 3);
        vendor = sqlite3_column_text(stmt, 4);
        name = sqlite3_column_text(stmt, 5);
        price = sqlite3_column_double(stmt, 6);
        url = sqlite3_column_text(stmt, 7);

        listViewObj.SetRow((const char*)name, i, 0);
        resultadoSQL = to_string(quantity);
        listViewObj.SetRow(resultadoSQL.c_str(), i, 1);
        resultadoSQL = "R$" + to_string((int)price) + ",00";
        listViewObj.SetRow(resultadoSQL.c_str(), i, 2);
        resultadoSQL = "R$" + to_string(((int)price) * quantity) + ",00";
        listViewObj.SetRow(resultadoSQL.c_str(), i, 3);
        listViewObj.SetRow((const char*)date, i, 4);
        listViewObj.SetRow((const char*)vendor, i, 5);
        
        i++;
        error = sqlite3_step(stmt);
    } while (error != SQLITE_DONE);
   
    sqlite3_close(db);
}

void showProduct(ListView& listViewObj, const char* brand) {
    //------ Database - Product ------------//
    int rc, rc2;
    int error = 0, i = 0;
    sqlite3* db;
    sqlite3_stmt* stmt = nullptr;
    sqlite3_stmt* stmt2 = nullptr;
    int warranty;
    double price;
    const unsigned char* name, * model, * dimensions, * weight, *url;
    stringstream resultadoSQL;

    ImageListManager *myImageListManager = new ImageListManager(50, 50, ILC_COLOR32 | ILC_HIGHQUALITYSCALE, 1, 20);

    //--------- Database ---------//
    sqlite3_open("SQL\\LojaTI.db", &db); // Se o Bando de Dados não existir ele é criado
    
    if (brand == "Kingston") {
        // Faz uma consulta na Tabela e envia para stmt
        rc = sqlite3_prepare_v2(db, "select Name, Price, Url from Product where Brand=\"kingston\";", -1, &stmt, 0);
        rc2 = sqlite3_prepare_v2(db, "select Model, Warranty, Dimensions, Weight from Technical where Brand=\"kingston\";", -1, &stmt2, 0);
    }
    else if (brand == "Logitech") {
        // Faz uma consulta na Tabela e envia para stmt
        rc = sqlite3_prepare_v2(db, "select Name, Price, Url from Product where Brand=\"Logitech\";", -1, &stmt, 0);
        rc2 = sqlite3_prepare_v2(db, "select Model, Warranty, Dimensions, Weight from Technical where Brand=\"Logitech\";", -1, &stmt2, 0);
    }

    error = sqlite3_step(stmt);
    sqlite3_step(stmt2);
    do {
        name = sqlite3_column_text(stmt, 0);
        price = sqlite3_column_double(stmt, 1);
        url = sqlite3_column_text(stmt, 2);
        model = sqlite3_column_text(stmt2, 0);
        warranty = sqlite3_column_int(stmt2, 1);
        dimensions = sqlite3_column_text(stmt2, 2);
        weight = sqlite3_column_text(stmt2, 3);

        listViewObj.SetRow((const char*)name, i, 0);
        listViewObj.SetRow((const char*)model, i, 1);
        resultadoSQL << "R$ " << price << ",00";
        listViewObj.SetRow(resultadoSQL.str().c_str(), i, 2);
        resultadoSQL.str("");
        resultadoSQL << warranty << " meses";
        listViewObj.SetRow(resultadoSQL.str().c_str(), i, 3);
        listViewObj.SetRow((const char*)dimensions, i, 4);
        listViewObj.SetRow((const char*)weight, i, 5);
        resultadoSQL.str("");
        resultadoSQL << "Resources\\productsImgICO\\" << url << "1.ico";
        myImageListManager->AddIcon(resultadoSQL.str().c_str());

        i++;
        resultadoSQL.str("");
        error = sqlite3_step(stmt);
        sqlite3_step(stmt2);
    } while (error != SQLITE_DONE);

    sqlite3_close(db);
    // Adiciona os ícones a ListView
    ListView_SetImageList(listViewObj.hListView, myImageListManager->hImageList, LVSIL_SMALL);
}
