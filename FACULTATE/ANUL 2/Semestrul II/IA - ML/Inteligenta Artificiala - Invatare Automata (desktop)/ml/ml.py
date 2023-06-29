import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
from tensorflow.keras.models import Sequential

# Definim arhitectura modelului CNN
model = Sequential([
    layers.Conv2D(16, (3,3), activation='relu', input_shape=(256, 256, 3)),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Conv2D(32, (3,3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Conv2D(64, (3,3), activation='relu'),
    layers.MaxPooling2D(pool_size=(2,2)),
    layers.Flatten(),
    layers.Dense(512, activation='relu'),
    layers.Dense(1, activation='sigmoid')
])

# Compilam modelul cu o functie de pierdere si un algoritm de optimizare
model.compile(
    loss='binary_crossentropy',
    optimizer='adam',
    metrics=['accuracy']
)

# Incarcam imaginile de antrenament si validare
train_data = keras.preprocessing.image.ImageDataGenerator(rescale=1./255).flow_from_directory(
    'train_dir',
    target_size=(256,256),
    batch_size=32,
    class_mode='binary'
)

val_data = keras.preprocessing.image.ImageDataGenerator(rescale=1./255).flow_from_directory(
    'val_dir',
    target_size=(256,256),
    batch_size=32,
    class_mode='binary'
)

# Antrenam modelul pe datele de antrenament si validare
model.fit(
    train_data,
    validation_data=val_data,
    epochs=10
)

# Salvam modelul antrenat
model.save('tomography_classification_model.h5')