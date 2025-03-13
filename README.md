# Warehouse project
 
# Food Warehouse Management System

## **Overview**
The **Food Warehouse Management System** is a **C++ simulation project** that models a warehouse for distributing food orders during a war. The system manages **customers (soldiers and civilians)**, assigns **volunteers (collectors and drivers)** to process orders, and executes simulation steps to manage the workflow. The project demonstrates **Object-Oriented Programming (OOP)** principles, including **The Rule of Five**, and ensures efficient memory management.

## **Features**
- Simulates a **real-time warehouse** with customers, volunteers, and orders.
- Implements **order management**, including creation, processing, and delivery.
- Supports **simulation steps** to update order status dynamically.
- Includes **logging, backup, and restore functionalities**.
- Uses **The Rule of Five** for proper memory handling in C++.

## **Installation & Compilation**
1. **Clone the repository**:
   ```sh
   git clone https://github.com/YarinBinyamin/FoodWarehouseManagement.git
   cd FoodWarehouseManagement
   ```
2. **Compile the project using Makefile**:
   ```sh
   make
   ```
   - The executable file will be created in the `bin/` folder.

## **Usage**
To run the program, provide the path to the configuration file:
```sh
./bin/warehouse example_input.txt
```
### **Supported Commands**
- `step <n>` → Move the simulation forward by `n` steps.
- `order <customer_id>` → Place an order for a customer.
- `customer <name> <type> <distance> <max_orders>` → Add a new customer.
- `orderStatus <order_id>` → Get details of an order.
- `customerStatus <customer_id>` → View customer orders and remaining order quota.
- `volunteerStatus <volunteer_id>` → Check volunteer status.
- `log` → Print all executed actions.
- `close` → Close the warehouse and print all order statuses.
- `backup` → Save the warehouse state.
- `restore` → Restore the last saved warehouse state.

## **Example Input File**
Example of a configuration file:
```txt
customer Maya soldier 4 2
customer David civilian 3 1
volunteer Noya collector 2
volunteer Ibrahim limited_collector 3 2
volunteer Din limited_driver 13 4 2
volunteer Limor driver 8 3
```

## **Memory Management & Debugging**
- The project follows **The Rule of Five** for resource management.
- Run **Valgrind** to check for memory leaks:
  ```sh
  valgrind --leak-check=full --show-reachable=yes ./bin/warehouse example_input.txt
  ```

## **Project Structure**
```
📂 FoodWarehouseManagement/
│── 📂 src/              # Contains all .cpp files
│── 📂 include/          # Contains all header (.h) files
│── 📂 bin/              # Empty directory for compiled binaries
│── Makefile             # Build script to compile the project
│── README.md            # Project documentation
│── example_input.txt    # Sample configuration file
```

## **Contribution**
Feel free to contribute by:
- Reporting issues
- Suggesting improvements
- Submitting pull requests

## **License**
This project is licensed under the **MIT License**.
