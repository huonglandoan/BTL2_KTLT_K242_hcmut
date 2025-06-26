Để chạy được testcases, các bạn copy file tay_nguyen...cpp và tay_nguyen...h bỏ vào cùng folder chạy tests.

Dùng IDE (suggest VSC) mở powershell hay right + click -> Open in Terminal để mở Terminal tại địa chỉ folder test.

Với lần đầu chạy test:

+ Lấy output:

g++ -o main main.cpp tay_nguyen_campaign.cpp -I . -std=c++11

Từ lần thứ hai trở đi:

+ Lấy output:

g++ -o main main.cpp tay_nguyen_campaign.cpp -I . -std=c++11; ./main RunOutput

+ Chạy test:

g++ -o main main.cpp tay_nguyen_campaign.cpp -I . -std=c++11; ./main RunTest