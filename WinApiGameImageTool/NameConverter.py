from PIL import Image
import os

class CNameConverter:
    def __init__(self):
        self.m_Directory = ""

    def SetDirectory(self, _path: str):
        self.m_Directory = _path

    def ConvertAll(self, strTarget, strToReplace):
        for root, dirs, files in os.walk(self.m_Directory):
            for f in files:
                oldName = root + "\\" + f
                newName = root + "\\" + f.replace(strTarget, strToReplace)
                os.rename(oldName, newName)





if __name__ == "__main__":
    NameConverter = CNameConverter()
    NameConverter.SetDirectory(r"F:\CppProject\CrazyArcadePortfolio2\CrazyArcadeGame\Resources\GUI")
    NameConverter.ConvertAll("Bazzi", "")