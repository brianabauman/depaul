import { Component, OnInit, OnDestroy, ViewChild, ElementRef } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Subscription } from 'rxjs';

import { environment } from '../../environments/environment'
import { Router } from '@angular/router';

@Component({
    selector: 'app-webcam-screenshot',
    templateUrl: './webcam-screenshot.component.html',
    styleUrls: ['./webcam-screenshot.component.css']
})
export class WebcamScreenshotComponent implements OnInit, OnDestroy {
  @ViewChild("video", { static: false })
  public video: ElementRef;
  @ViewChild("canvas", { static: false })
  public canvas: ElementRef;
  public captures: Array<any>;
  public text: string = "";
  cloudResponseSub: Subscription;
  cloudSubOpened: boolean = false;

  public constructor(
    private http: HttpClient,
    private router: Router
  ) {
      this.captures = [];
  }

  public ngOnInit() { }

  ngOnDestroy() {
    if (this.cloudSubOpened) { this.cloudResponseSub.unsubscribe(); }
  }

  public ngAfterViewInit() {
    if(navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
      navigator.mediaDevices.getUserMedia({ video: true }).then(stream => {
        this.video.nativeElement.srcObject = stream;
        this.video.nativeElement.play();
      });
    }
  }

  public async capture() {
    this.text = "";

    let context = this.canvas.nativeElement.getContext("2d").drawImage(this.video.nativeElement, 0, 0, 640, 480);
    const image = this.canvas.nativeElement.toDataURL("image/png");
    const base64Image = image.replace(/^data:image\/(png|jpg|jpeg);base64,/, "");
    this.captures.push(image);

    this.cloudSubOpened = true;
    this.cloudResponseSub = this.http.post(
      `https://vision.googleapis.com/v1/images:annotate?key=${environment.cloudVisionApiKey}`, 
      { 
        "requests": [
          {
            "image": {
              "content": base64Image
            },
            "features": [
              {
                "type": "TEXT_DETECTION"
              }
            ]
          }
        ]
      },
      { }
    ).subscribe(resp => { 
      this.text = resp["responses"][0].fullTextAnnotation.text;
      if (this.text == "") { 
        alert("No text identified. Please try again."); 
      } else {
        this.text = this.text.replace('\/', "");
        this.router.navigate([`add/${this.text}`]); 
      }
    });
  }
}