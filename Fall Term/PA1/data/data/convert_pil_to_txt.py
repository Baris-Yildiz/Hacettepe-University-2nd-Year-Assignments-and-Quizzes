from PIL import Image

def image_to_txt(filepath, output_path):
    image = Image.open(filepath).convert('L')  # Convert to grayscale
    width, height = image.size
    
    with open(output_path, 'w') as f:
        for y in range(height):
            for x in range(width):
                pixel_value = image.getpixel((x, y))
                f.write(f"{pixel_value} ")
            f.write("\n")

if __name__ == "__main__":
    image_to_txt("10.png", "output.txt")

