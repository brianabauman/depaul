import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatApp } from './chat-app.component';

describe('ChatAppComponent', () => {
  let component: ChatApp;
  let fixture: ComponentFixture<ChatApp>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ChatApp ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ChatApp);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
