# DecisionTree
 C++
 **Thuật toán xây dựng cây quyết định (Decision Tree) để dự đoán tập dữ liệu sau :**
 Title                : Balance Scale Weight & Distance Database
 Number of Instances  : 625 (49 balanced, 288 left, 288 right)
 Number of Attributes : 4 (numeric) + class name = 5
 Attribute Information:
 Class Name (Target variable): 3
 L [balance scale tip to the left]
 B [balance scale be balanced]
 R [balance scale tip to the right]
 Left-Weight: 5 (1, 2, 3, 4, 5)
 Left-Distance: 5 (1, 2, 3, 4, 5)
 Right-Weight: 5 (1, 2, 3, 4, 5)
 Right-Distance: 5 (1, 2, 3, 4, 5)
 Missing Attribute Values: None
 Class Distribution:
 46.08 percent are L
 07.84 percent are B
 46.08 percent are R
 **Implement:**
 _Thông tin của 1 node_
 struct nodeInfo {
    bool isLeaf = 0;
    int id, value;
 };
_ Một node bao gồm địa chỉ 2 node con, thông tin 1 node và nhãn_
 struct Node {
    Node* left;
    Node* right;
    nodeInfo nodeInfo;
    char ans;
 };
 **Cây bao gồm địa chỉ node gốc**
 struct Tree
 {
    Node* root = new Node;
 };
 
 **Phần cài đặt các hàm của cây được trình bày ở đây : **
 https://www.canva.com/design/DAEwvjcrGxE/share/preview?token=IzI4t5fDRPD2Mzf5MHhFgg&role=EDITOR&utm_content=DAEwvjcrGxE&utm_campaign=designshare&utm_medium=link&utm_source=sharebutton
 
 **Tối ưu cho Decision Tree:**
 Cải tiến 1 : 
 Vì dữ liệu của tập train cho mỗi thuộc tính là từ 1 đến 5. Vì vậy, thay vì mỗi thuộc tính ta duyệt toàn bộ giá trị là 439 giá trị để tính giniScore. Ta sẽ duyệt từ 1 -> 5 thay  vì 439 giá trị. Chúng ta sẽ giảm được tốc độ đi 88 lần
 Cải tiến 2 :
 Đánh giá lại các Hyper parameter như : minSize, maxDepth để tối ưu được độ chính xác. Như ở trong thuật toán trên Hyper parameter được đánh giá sau khi cài đặt Random Forest
 Cải tiến 3 :
 Sử dụng Random Forest để giảm overfitting. 
 Cải tiến 4 :
 Đánh giá thêm về việc cân bằng nhãn "B" trong tập train.txt để giúp tăng độ chính xác
 **Chi tiết về các cải tiến của Decision Tree được trình bày chi tiết trong slide :**
 https://www.canva.com/design/DAEwvjcrGxE/share/preview?token=IzI4t5fDRPD2Mzf5MHhFgg&role=EDITOR&utm_content=DAEwvjcrGxE&utm_campaign=designshare&utm_medium=link&utm_source=sharebutton
                                                                                        **The End**
