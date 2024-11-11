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
    AutoCutter.SetDirectory(r"C:\Users\33kkm\Desktop\BombExplosionBefore")
    AutoCutter.SetImageFileName(r"Balloons.png")
    AutoCutter.SetOutputDirectory(r"C:\Users\33kkm\Desktop\BombExplosionAfter")
    AutoCutter.SetImageSize(40, 40)

    for i in range(0, 14):
        AutoCutter.AddPixelCoordinate(5 + i * 40, 567)
    for i in range(0, 14):
        AutoCutter.AddPixelCoordinate(5 + i * 40, 607)
    for i in range(0, 14):
        AutoCutter.AddPixelCoordinate(5 + i * 40, 647)
    for i in range(0, 14):
        AutoCutter.AddPixelCoordinate(5 + i * 40, 687)
    for i in range(0, 4):
        AutoCutter.AddPixelCoordinate(5 + i * 40, 727)

    AutoCutter.InitiateCutting()