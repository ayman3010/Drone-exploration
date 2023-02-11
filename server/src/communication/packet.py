from dataclasses import dataclass


@dataclass
class Packet:
    idx: int
    pos_x : float
    pos_y : float
    obs_right : float
    obs_left : float
    obs_front : float
    obs_back : float
    battery_level : float
    crashed : bool

    def get_object(self):
        return {
            "idx": self.idx,
            "pos_x" : self.pos_x,
            "pos_y" : self.pos_y,
            "obs_right" : self.obs_right,
            "obs_left" : self.obs_left,
            "obs_front" : self.obs_front,
            "obs_back" : self.obs_back,
            "battery_level" : self.battery_level,
            "crashed" : self.crashed
        }