#include "error_signal.hpp"

ErrorSignal* ErrorSignal::m_instance = nullptr;

ErrorSignal::ErrorSignal() {
    if (m_instance == nullptr) {
        m_instance = this;
    }
}