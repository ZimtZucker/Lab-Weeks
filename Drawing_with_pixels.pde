void setup() {
size(500, 500);
smooth();
background(204, 255, 153);
}

void draw() {

for (int l = 0;l < width;l+=20) {
float paint = map(l, 0, width, 200, 360);
for (int k = 0; k < height;k+=20) {
if (mouseX > l && mouseX < l +20 && mouseY > k && mouseY < k+20 && mousePressed) {

fill(paint, 0, 125, 100);
}
else {
noFill();
}

rect(l, k, 20, 20);

}
}
}
