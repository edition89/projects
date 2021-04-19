class Designer(object):
    def __init__(self, work = False, awards = 0):
        self.work = work
        self.awards = awards
        if(work and awards < 2):
            self.awards = 2
        
    def add_awards(self, count = 1):
        self.awards = self.awards + count
        
    def worked(self, work):
        self.work = work
        if(self.work and self.awards < 2):
            self.awards = 2
        
    def get_grade(self):
        print("Ваш грейд: " + str((self.awards * 2)// 7))
    
des_1 = Designer()
des_2 = Designer(True)
des_3 = Designer(False, 5)
des_4 = Designer(True, 1)
des_5 = Designer(True, 3)
des_1.get_grade()
print(des_1.work)
print(des_1.awards)
des_1.worked(True)
print(des_1.work)
print(des_1.awards)
des_1.add_awards()
print(des_1.work)
print(des_1.awards)
des_1.add_awards(5)
print(des_1.work)
print(des_1.awards)
des_1.get_grade()
des_2.get_grade()
des_3.get_grade()
des_4.get_grade()
des_5.get_grade()
