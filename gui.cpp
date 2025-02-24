#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

class Minesweeper : public QWidget {
public:
    Minesweeper(int rows, int cols, QWidget *parent = nullptr) : QWidget(parent) {
        // Set up the grid layout
        QGridLayout *layout = new QGridLayout(this);
        layout->setSpacing(1); // Small gap between buttons

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                QPushButton *button = new QPushButton("");
                button->setFixedSize(40, 40); // Set size of each button
                layout->addWidget(button, row, col);

                // Optional: Connect button to a simple click handler
                connect(button, &QPushButton::clicked, this, [=]() {
                    button->setText("X"); // For example, mark the cell
                });
            }
        }
        setLayout(layout);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the Minesweeper grid
    Minesweeper window(10, 10); // 10x10 grid
    window.setWindowTitle("Minesweeper");
    window.show();

    return app.exec();
}