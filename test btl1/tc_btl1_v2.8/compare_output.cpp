#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// Hàm so sánh nội dung hai file
bool compareFiles(const string &file1, const string &file2) {
    ifstream f1(file1), f2(file2);
    if (!f1.is_open() || !f2.is_open()) {
        cerr << "Không thể mở file: " << file1 << " hoặc " << file2 << endl;
        return false;
    }
    stringstream ss1, ss2;
    ss1 << f1.rdbuf();
    ss2 << f2.rdbuf();
    return (ss1.str() == ss2.str());
}

int main() {
    vector<string> differentFiles; // Lưu danh sách các file có sự khác biệt
    int totalFiles = 0, differentCount = 0;

    // Duyệt qua tất cả các file trong thư mục "answer/"
    for (const auto &entry : fs::directory_iterator("answer")) {
        string answerFile = entry.path().string();
        string fileName = entry.path().filename().string();
        string outputFile = "output/" + fileName; // Thay đổi đường dẫn tới thư mục output

        totalFiles++;
        
        if (!fs::exists(outputFile)) {
            cerr << "❌ Không tìm thấy file output tương ứng: " << outputFile << endl;
            continue;
        }

        if (!compareFiles(answerFile, outputFile)) {
            differentFiles.push_back(fileName);
            differentCount++;
        }
    }

    // In kết quả
    cout << "📌 Tổng số file kiểm tra: " << totalFiles << endl;
    cout << "✅ Số file giống nhau: " << (totalFiles - differentCount) << endl;
    cout << "❌ Số file khác nhau: " << differentCount << endl;

    if (!differentFiles.empty()) {
        cout << "📂 Các file khác nhau:\n";
        for (const string &file : differentFiles) {
            cout << "   - " << file << endl;
        }
    } else {
        cout << "🎉 Tất cả file đều giống nhau!\n";
    }

    return 0;
}
