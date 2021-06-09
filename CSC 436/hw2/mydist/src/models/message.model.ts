import { User } from './user.model';

export class Message {
  text: string;
  timestamp: string;
  to: User;
  from: User;
}