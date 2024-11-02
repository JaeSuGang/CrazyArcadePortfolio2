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
                if f.endswith(".png"):
                    file_directory = root
                    file_name = f
                    self.__ConvertPngFile(file_directory, file_name)

    def __ConvertPngFile(self, file_directory: str, file_name: str):
        # PNG 파일 열기
        file_path = file_directory + "\\" + file_name
        output_path = self.m_OutputDirectory + "\\" + file_name.replace(".png", ".bmp")
        img = Image.open(file_path).convert("RGBA")
        width, height = img.size
        width = int(width * 1.5)
        height = int(height * 1.5)
        img = img.resize((width, height), Image.NEAREST)

        # 새로운 이미지 생성 (RGB 모드)
        new_img = Image.new("RGB", (width, height))

        # 픽셀 데이터 가져오기
        pixels = img.load()
        new_pixels = new_img.load()

        # 알파 값이 0인 경우 마젠타 색으로 변환
        for y in range(height):
            for x in range(width):
                r, g, b, a = pixels[x, y]
                if a == 0:
                    new_pixels[x, y] = (255, 0, 255)  # 마젠타 색
                else:
                    new_pixels[x, y] = (r, g, b)

        # BMP 파일로 저장
        new_img.save(output_path, "BMP")


if __name__ == "__main__":
    BmpConverter = CBmpConverter()
    BmpConverter.SetDirectory(r"F:\CppProject\CrazyArcadePortfolio2\CrazyArcadeGame\Resources\GUI")
    BmpConverter.SetOutputDirectory(r"F:\CppProject\CrazyArcadePortfolio2\CrazyArcadeGame\Resources\GUI")
    BmpConverter.ConvertAll()