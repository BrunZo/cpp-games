/* 
 * File:   state.h
 * Author: Bruno
 *
 * Created on 6 de marzo de 2018, 18:32
 */

#ifndef STATE_H
#define STATE_H

class State
{
    public:
        virtual void init(RECT* prc){};
        virtual void update(RECT* prc){};
        virtual void draw(HDC hdc, HDC hdcBuffer){};
};

#endif /* STATE_H */

