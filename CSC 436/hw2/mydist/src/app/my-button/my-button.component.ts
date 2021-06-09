import { Component, OnInit } from '@angular/core';
import { MyServiceService } from '../my-service.service';

@Component({
  selector: 'app-my-button',
  templateUrl: './my-button.component.html',
  styleUrls: ['./my-button.component.css']
})
export class MyButtonComponent implements OnInit {

  liked: boolean = false;

  constructor(private myService: MyServiceService) { }

  ngOnInit() { }

  buttonWasClicked(): void {
      this.liked = this.myService.likeImage(this.liked);
  }
}
