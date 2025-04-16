//
// Created by EgorRychkov on 10.04.2025.
//

#ifndef LOGISTICHELL_ENGINECONTEXT_H
#define LOGISTICHELL_ENGINECONTEXT_H

class Application;

class EngineContext {
public:
    Application *app = nullptr;
    float last_frame_delta_time = 0;
};


#endif //LOGISTICHELL_ENGINECONTEXT_H
