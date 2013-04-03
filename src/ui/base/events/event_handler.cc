// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/base/events/event_dispatcher.h"
#include "ui/base/events/event_handler.h"

#include "ui/base/events/event.h"

namespace ui {

EventHandler::EventHandler() {
}

EventHandler::~EventHandler() {
  while (!dispatchers_.empty()) {
    EventDispatcher* dispatcher = dispatchers_.top();
    dispatchers_.pop();
    dispatcher->OnHandlerDestroyed(this);
  }
}

void EventHandler::OnEvent(Event* event) {
  if (event->IsKeyEvent())
    OnKeyEvent(static_cast<KeyEvent*>(event));
  else if (event->IsMouseEvent())
    OnMouseEvent(static_cast<MouseEvent*>(event));
  else if (event->IsScrollEvent())
    OnScrollEvent(static_cast<ScrollEvent*>(event));
  else if (event->IsTouchEvent())
    OnTouchEvent(static_cast<TouchEvent*>(event));
  else if (event->IsGestureEvent())
    OnGestureEvent(static_cast<GestureEvent*>(event));
}

void EventHandler::OnKeyEvent(KeyEvent* event) {
}

void EventHandler::OnMouseEvent(MouseEvent* event) {
}

void EventHandler::OnScrollEvent(ScrollEvent* event) {
}

void EventHandler::OnTouchEvent(TouchEvent* event) {
}

void EventHandler::OnGestureEvent(GestureEvent* event) {
}

}  // namespace ui