import hashing_mod

trainData = []
validData= []

hashing_mod.read_csv("C:/Users/artem/Desktop/labs/algoritms/lab2.2/entrypoint/data_train.csv", trainData)
hashing_mod.read_csv("C:/Users/artem/Desktop/labs/algoritms/lab2.2/entrypoint/dataset.csv", validData)
    
model = hashing_mod.LogisticRegression()

model.train(trainData, validData)

metrics = model.evalute(validData)

print(metrics)