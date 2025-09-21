import threading
from abc import ABC, abstractmethod
from dataclasses import dataclass


@dataclass
class Event(ABC):
    pin: int

    @abstractmethod
    def __call__(self, *args, **kwargs):
        ...

@dataclass
class EventHandler(ABC):
    event: Event
    
    @abstractmethod
    def __call__(self, *args, **kwargs):
        ...

class HAL:
    def __init__(self):
        self.events = []
        self.event_threads = []
    
    def monitor_event(self, event: Event):
        ...
    
    def start(self):
        for event in self.events:
            thread = threading.Thread(target=self.monitor_event, args=(event,))
            thread.daemon = True
            thread.start()
            self.event_threads.append(thread)