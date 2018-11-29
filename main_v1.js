let canvas = document.getElementById("canvas");
const W = 768;
const H = 480;
canvas.width = W;
canvas.height = H;
let ctx = canvas.getContext('2d');

ctx.fillStyle = 'chartreuse';
ctx.strokeStyle = 'black'

// Set line width
ctx.lineWidth = 10;

// Wall
ctx.strokeRect(75, 140, 150, 110);

// Door
ctx.fillRect(130, 190, 40, 60);

// Roof
ctx.moveTo(50, 140);
ctx.lineTo(150, 60);
ctx.lineTo(250, 140);
ctx.closePath();
ctx.stroke();

var particles = [];

function new_particle(start_frame) {
	return {
		x: W/2 + Math.random()*50-25,
		y: H,
		r: 255,
		g: 255,
		b: 0,
		size: 1,
		vx: Math.random()*16 - 8,
		vy: Math.random()*8-32,
		frame: start_frame || (Math.random()*60)|0
	};
}

const PARTICLES = 100000
for (var i = 0; i < PARTICLES; i++) {
	particles[i] = new_particle();
}
ctx.imageSmoothingEnabled = false;
var cur_frame = 0;
var curtime = performance.now();
var slider = document.getElementById("slider");
var draw
draw = function() {
	++cur_frame;
	ctx.clearRect(0, 0, W, H);
	ctx.fillStyle = 'black';
	var particles_shown = slider.value;
	for (var i = 0; i < particles_shown; i++) {
		var p = particles[i];
		if (cur_frame < p.frame) { continue };

		var oldx = p.x;
		var oldy = p.y;
		p.x += p.vx;
		p.y += p.vy;

		if (p.y > H) {
			particles[i] = new_particle(cur_frame);
		}

		p.size *= 0.97;

		p.r *= 0.95;
		p.g *= 0.9;

		p.vy += 1;

		ctx.beginPath();
		ctx.lineWidth = p.size;
		ctx.strokeStyle = 'rgb('+p.r+','+p.g+','+p.b+')';
		ctx.moveTo(oldx, oldy)
		ctx.lineTo(p.x, p.y);
		ctx.stroke()
		ctx.closePath();

	};
	var now = performance.now();
	ctx.fillText(((now - curtime)|0) + 'ms', 5, 10);
	ctx.fillText(particles_shown + ' particles', 5, 25);
	curtime = now;
	window.requestAnimationFrame(draw);
}
window.requestAnimationFrame(draw);
