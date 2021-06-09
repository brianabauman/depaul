import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatLogin } from './chat-login.component';

describe('ChatLoginComponent', () => {
  let component: ChatLogin;
  let fixture: ComponentFixture<ChatLogin>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ChatLogin ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ChatLogin);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
