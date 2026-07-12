#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    // 2. Instantiate the button on the Heap
    // Passing 'this' tells Qt that this window owns the button
    myButton = new QPushButton("Click Me!", this);

    // 3. Customize basic syntax properties (Optional)
    myButton->setFixedSize(100, 40);         // Width, Height in pixels
    myButton->setProperty("custom_tag", 42); // Attaching data

    // 4. Arrange widgets using a basic layout manager
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(myButton);

    // 5. Connect the Click Event to your member function slot
    connect(myButton, &QPushButton::clicked, this, &GameWindow::onButtonClicked);
}

void GameWindow::onButtonClicked()
{
    std::cout << "The button was clicked!" << std::endl;

    // Example of reading your attached property back out
    int tagValue = myButton->property("custom_tag").toInt();
    std::cout << "Stored tag value is: " << tagValue << std::endl;
}