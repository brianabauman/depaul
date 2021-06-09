import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ChatNavBar } from './nav-bar.component';

describe('ChatNavBar', () => {
  let component: ChatNavBar;
  let fixture: ComponentFixture<ChatNavBar>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ChatNavBar ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ChatNavBar);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
