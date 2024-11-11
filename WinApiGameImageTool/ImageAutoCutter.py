from PIL import Image


class CAutoCutter:
    def __init__(self):
        self.m_ImageFileName = ""
        self.m_Directory = ""
        self.m_OutputDirectory = ""
        self.m_ImageSizeX = 0
        self.m_ImageSizeY = 0
        self.m_PixelsToStartCutting = []

    def InitiateCutting(self):
        file_path = self.m_Directory + "\\" + self.m_ImageFileName
        output_path = self.m_OutputDirectory + "\\" + self.m_ImageFileName
        img = Image.open(file_path).convert("RGBA")

        pixels = img.load()
        width, height = img.size
        for y in range(height):
            for x in range(width):
                r, g, b, a = pixels[x, y]
                if a == 0:
                    pixels[x, y] = (255, 0, 255, 255)

        count = 0
        for Pixel in self.m_PixelsToStartCutting:
            cropped_image = img.crop(
                (Pixel[0], Pixel[1],
                 Pixel[0] + self.m_ImageSizeX,
                 Pixel[1] + self.m_ImageSizeY))
            cropped_image.save("{0}\\{1}.bmp".format(self.m_OutputDirectory, count)
                               , format="BMP")
            count += 1


    def AddPixelCoordinate(self, x, y):
        self.m_PixelsToStartCutting.append([x, y])

    def SetImageSize(self, x, y):
        self.m_ImageSizeX = x
        self.m_ImageSizeY = y

    def SetImageFileName(self, _path: str):
        self.m_ImageFileName = _path

    def SetDirectory(self, _path: str):
        self.m_Directory = _path

    def SetOutputDirectory(self, _path: str):
        self.m_OutputDirectory = _path



if __name__ == "__main__":
    AutoCutter = CAutoCutter()
    AutoCutter.SetDirectory(r"C:\Users\33kkm\Desktop\Before")
    AutoCutter.SetImageFileName(r"bombwater.png")
    AutoCutter.SetOutputDirectory(r"C:\Users\33kkm\Desktop\After")
    AutoCutter.SetImageSize(40, 41)

    AutoCutter.AddPixelCoordinate(28, 114)
    AutoCutter.AddPixelCoordinate(85, 114)
    AutoCutter.AddPixelCoordinate(143, 114)

    AutoCutter.AddPixelCoordinate(28, 185)
    AutoCutter.AddPixelCoordinate(86, 185)
    AutoCutter.AddPixelCoordinate(145, 185)
    AutoCutter.AddPixelCoordinate(202, 185)

    AutoCutter.AddPixelCoordinate(276, 185)
    AutoCutter.AddPixelCoordinate(334, 185)
    AutoCutter.AddPixelCoordinate(393, 185)
    AutoCutter.AddPixelCoordinate(448, 184)

    AutoCutter.AddPixelCoordinate(28, 260)
    AutoCutter.AddPixelCoordinate(86, 260)
    AutoCutter.AddPixelCoordinate(145, 260)
    AutoCutter.AddPixelCoordinate(202, 260)

    AutoCutter.AddPixelCoordinate(272, 260)
    AutoCutter.AddPixelCoordinate(333, 260)
    AutoCutter.AddPixelCoordinate(384, 260)
    AutoCutter.AddPixelCoordinate(436, 260)

    AutoCutter.AddPixelCoordinate(28, 344)
    AutoCutter.AddPixelCoordinate(85, 344)
    AutoCutter.AddPixelCoordinate(146, 344)
    AutoCutter.AddPixelCoordinate(202, 344)

    AutoCutter.AddPixelCoordinate(271, 344)
    AutoCutter.AddPixelCoordinate(335, 344)
    AutoCutter.AddPixelCoordinate(389, 344)
    AutoCutter.AddPixelCoordinate(446, 344)

    AutoCutter.AddPixelCoordinate(28, 419)
    AutoCutter.AddPixelCoordinate(85, 419)
    AutoCutter.AddPixelCoordinate(145, 419)
    AutoCutter.AddPixelCoordinate(202, 419)

    AutoCutter.AddPixelCoordinate(271, 419)
    AutoCutter.AddPixelCoordinate(325, 419)
    AutoCutter.AddPixelCoordinate(379, 419)
    AutoCutter.AddPixelCoordinate(444, 419)

    AutoCutter.InitiateCutting()