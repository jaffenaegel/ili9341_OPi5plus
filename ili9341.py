import ctypes
import time
from PIL import Image
import numpy as np


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

        self.__sending_image = lib.DisplayImage
        self.__sending_image.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_int]

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
        Displays two colors alternating rapidly for the number of frames provided. Then calculates how many frames were displayed per second on average
        and returns that number.
        """
        if type(number_of_frames) != int:
            raise TypeError("Argument 'number_of_frames' must be of type int")
        return self.__test(number_of_frames)

    def __send_bytes(self, data):
        self.__sending_image((ctypes.c_uint8 * len(data))(*data), len(data))

    def send_image(self, image):
        data = self.__image_to_bytes(image)
        self.__send_bytes(data)

    @staticmethod
    def __image_to_bytes(image, rotation=0):
        pb = np.rot90(image, (rotation // 90) - 1).astype("uint16")
        red = (pb[..., [0]] & 0xF8) << 8
        green = (pb[..., [1]] & 0xFC) << 3
        blue = (pb[..., [2]] & 0xF8) >> 3
        result = red | green | blue
        return result.byteswap().tobytes()


if __name__ == "__main__":
    img = Image.open("cat.jpg")
    ili = ILI9341()
    print(ili.test())
    time.sleep(1)
    ili.send_image(img)
    time.sleep(1)
