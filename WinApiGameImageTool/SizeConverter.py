from PIL import Image
import os

class CBmpConverter:
    def __init__(self):
        self.m_Directory = ""
        self.m_OutputDirectory = ""

    def SetDirectory(self, _path: str):
        self.m_Directory = _path

    def SetOutputDirectory(self, _path: str):
        self.m_OutputDirectory = _path

    def ConvertAll(self):
        for root, dirs, files in os.walk(self.m_Directory):
            for f in files:
                if f.endswith(".bmp"):
                    file_directory = root
                    file_name = f
                    self.__ConvertFile(file_directory, file_name)

    def __ConvertFile(self, file_directory: str, file_name: str):
        # PNG 파일 열기
        file_path = file_directory + "\\" + file_name
        output_path = self.m_OutputDirectory + "\\" + file_name
        img = Image.open(file_path)
        original_width, original_height = img.size
        new_width = int(66)
        new_height = int(original_height / original_width * new_width)
        new_size = (new_width, new_height)
        new_img = img.resize(new_size, Image.NEAREST)
        new_img.save(output_path)


if __name__ == "__main__":
    BmpConverter = CBmpConverter()
    BmpConverter.SetDirectory(r"C:\Users\33kkm\Desktop\ImageModify\3")
    BmpConverter.SetOutputDirectory(r"C:\Users\33kkm\Desktop\ImageModify")
    BmpConverter.ConvertAll()