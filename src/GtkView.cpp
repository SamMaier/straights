//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"
GtkView::GtkView(Game* game): game_(game), m_button("Sample") {
    set_border_width(10);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &GtkView::onButtonClicked));
    add(m_button);
    m_button.show();
}

void GtkView::onButtonClicked() {
  std::cout << "Button Clicked" << std::endl;
};
