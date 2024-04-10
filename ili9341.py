import ctypes
import time


class ILI9341:
    def __init__(self):
        lib = ctypes.CDLL("./ili9341.so")
        lib.Begin()
        self.__get_background_status = lib.GetBacklight

        self.__set_background_status = lib.SetBacklight
        self.__set_background_status.argtypes = [ctypes.c_bool]

        self.__test = lib.Test
        self.__test.argtypes = [ctypes.c_int]
        self.__test.restype = ctypes.c_double

    @property
    def background_led_enabled(self):
        """
        Gets and sets the background LED's of the display.
        """
        return self.__get_background_status() == 1

    @background_led_enabled.setter
    def background_led_enabled(self, value):
        if type(value) != bool:
            raise TypeError("Property 'background_led_enabled' must be of type bool.")
        self.__set_background_status(value)

    def test(self, number_of_frames=60):
        """
        Displays two colors alternating rapidly for the number of frames provided.
        Then it calculates how many frames were displayed per second on average and returns that number.
        """
        if type(number_of_frames) != int:
            raise TypeError("Argument 'number_of_frames' must be of type int")
        return self.__test(number_of_frames)


if __name__ == "__main__":
    ili = ILI9341()
    print(ili.test())
    ili.background_led_enabled = False
    time.sleep(1)
    print(ili.background_led_enabled)
