Các bạn có thể chạy theo nhiều cách, nhưng đây là cách các bạn có thể tham khảo:
- Các bạn cần có Visual Studio Code (VS xanh) và cài sẵn môi trường C++ trên máy.
- Sau khi giải nén, tại folder này click chuột phải vào khoảng trống, chọn Open with terminal, gõ "code ." để mở VS Code
- Trong VS Code, nhấn tổ hợp phím Ctrl + Shift + ` để mở terminal, hoặc cũng có thể dùng trực tiếp terminal mới mở ở trên
- Paste 2 file các bạn dùng để nộp bài vào đây (hứa không cài mã độc ăn cắp code)
- Build hàm main: g++ -o main main.cpp tay_nguyen_campaign.cpp -I . -std=c++11
- Sau đó chạy bằng lệnhh ./main
- Folder answer chứa đáp án của mình, bạn có thể đối chiếu với folder output (đáp án của bạn), hoặc tính thủ công với input ở folder testcase.
- g++ -o ss compare_output.cpp