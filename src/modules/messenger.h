
#pragma once
#include <vector>

class InputComponent {
public:
    //virtual void OnKeyEvent(int key_code, int key_state) = 0;
    //virtual void OnMouseKeyEvent(int key_code, int key_state) = 0;
};

class Messenger {
public:
    void OnProcessEvents();

    void RegisterInputReciver(InputComponent* input_component_reference);
    void MessageKeyRequest(int key_code, int key_state);
    void MouseKeyEventRequest(int key_code, int key_state);
    void MouseMoveEventRequest(int x_coordinate, int y_coordinate);

    std::vector<InputComponent*> input_message_listeners;
};
