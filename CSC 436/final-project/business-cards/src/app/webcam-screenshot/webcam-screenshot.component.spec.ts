import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { WebcamScreenshotComponent } from './webcam-screenshot.component';

describe('WebcamScreenshotComponent', () => {
  let component: WebcamScreenshotComponent;
  let fixture: ComponentFixture<WebcamScreenshotComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ WebcamScreenshotComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(WebcamScreenshotComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
