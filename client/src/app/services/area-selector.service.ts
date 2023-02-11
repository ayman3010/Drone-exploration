import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class AreaSelectorService {

  startX:number = 0;
  startY:number = 0;
  width: number = 0;
  height: number = 0;
  isSelecting:boolean = false;
  isDrawn: boolean = false;
  context: CanvasRenderingContext2D | null= null ;
  
  constructor() {}

  mouse_down(event:MouseEvent) {
    this.startX = event.offsetX;
    this.startY = event.offsetY;
    this.width = 0;
    this.height = 0;
    console.log(event);
    console.log('X: ', this.startX, ', Y: ', this.startY);
    this.isSelecting = true; 
  }

  mouse_move(event:MouseEvent) {
    console.log('isSelecting: ', this.isSelecting);
    if (!this.isSelecting) return;
    let dx = event.movementX;
    let dy = event.movementY;
    this.width += dx;
    this.height += dy;
  }

  mouse_up(event:MouseEvent) {
    this.isSelecting = false;
    let zoneData = {x: this.startX, y: this.startY, width: this.width, height: this.height};
    console.log(zoneData);
    if (this.width === 0 && this.height === 0) return;
    if(!this.isDrawn) {
      this.context?.fillRect(this.startX, this.startY, this.width, this.height);
      this.isDrawn = true;
    }
    
    this.width = 0;
    this.height = 0;
    return zoneData;
  }

  mouse_out(event:MouseEvent) {
    this.isSelecting = false;
    this.width = 0;
    this.height = 0;
  }

  scale(value: number,min: number, max: number, refLength: number) {
    let lowerBorne = value - min;
    let length = max - min;
    let percentage = lowerBorne / length;
    let positiveValue = percentage * refLength;
    return positiveValue - refLength / 2;
  }

}
